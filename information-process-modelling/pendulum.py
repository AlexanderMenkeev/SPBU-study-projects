import pybullet as p
import time
import pybullet_data
import numpy as np
import math

GUI = True

print("****************** \n1 - Интерполяция полиномом третьего порядка \n2 - Интерполяция полиномом пятого порядка \n" +
        "3 - Трапецевидный профиль скорости \n******************")
option = int(input())

if (GUI):
    physicsClient = p.connect(p.GUI)
    p.resetDebugVisualizerCamera(
        cameraDistance=1.2, 
        cameraYaw=90, 
        cameraPitch=0, 
        cameraTargetPosition=[0, 0, 1]
    )
    p.configureDebugVisualizer(p.COV_ENABLE_GUI, 0)
    p.addUserDebugLine([0,0,0],[1,0,0],[1,0,0],4)
    p.addUserDebugLine([0,0,0],[0,1,0],[0,1,0],4)
    p.addUserDebugLine([0,0,0],[0,0,1],[0,0,1],4)
    p.setAdditionalSearchPath(pybullet_data.getDataPath())
    planeID = p.loadURDF('plane.urdf')
else:
    physicsClient = p.connect(p.DIRECT)


g = 9.8
m = 1
L = 0.5
kf = 0.1
p.setGravity(0, 0, -g)
bodyId = p.loadURDF("./pendulum.urdf")


q0 = -0.8 # starting position
dt = 1/240 # pybullet simulation step
t = 0
T = 2
maxTime = T + T / 4

logTime = np.arange(0.0, maxTime, dt)
sz = logTime.size
logPos = np.zeros(sz)
logVel = np.zeros(sz)
logAcc = np.zeros(sz)
logJerk = np.zeros(sz)
logCtr = np.zeros(sz-1)
logPos[0] = q0
logRef = np.zeros(sz)
logRef[0] = q0
logRefd = np.zeros(sz)
logRefdd = np.zeros(sz)
logRefddd = np.zeros(sz)

# go to the starting position
p.setJointMotorControl2(bodyIndex = bodyId,
                        jointIndex = 1,
                        controlMode = p.POSITION_CONTROL,
                        targetPosition = q0)
for _ in range(1000):
    p.stepSimulation()

q0 = p.getJointState(bodyId, 1)[0]

# get rid of the default damping
p.changeDynamics(bodyId, 1, linearDamping = 0)

# let pendulum joint rotate freely
p.setJointMotorControl2(bodyIndex = bodyId,
                        jointIndex = 1,
                        controlMode = p.VELOCITY_CONTROL,
                        targetVelocity = 0,
                        force = 0)
idx = 1
pos = q0
vel = 0

kp = 5005
kv = 100
ki = 0
qd = 0.8

def trapezoidal_profile(Q_start, Q_end, T, t):
    v = 1.5 / T
    a = (v**2) / (v*T - 1)
    t_a = v / a
    s = ds = dds = 0
    if t <= t_a:
        s = 0.5*a*t**2
        ds = a*t
        dds = a
    elif t > t_a and t <= T - t_a:
        s = v*t - (v**2) / (2*a)
        ds = v
        dds = 0
    elif t > T - t_a and t <= T:
        s = (2*a*v*T - 2*v**2 - (a**2)*(t - T)**2) / (2*a)
        ds = a*(T-t)
        dds = -a

    Q = Q_start + s*(Q_end - Q_start)
    dQ = (Q_end - Q_start)*ds
    ddQ = (Q_end - Q_start)*dds
    
    return (s, Q, dQ, ddQ) if (t <= T) else (s, Q_end, 0, 0)

def fifth_order_poly_profile(Q_start, Q_end, T, t):
    a0 = 0
    a1 = 0
    a2 = 0
    a3 = 10 / T**3
    a4 = - 15 / T**4
    a5 = 6 / T**5
    s = a0 + a1*t + a2*t**2 + a3*t**3 + a4*t**4 + a5*t**5
    ds = a1 + 2*a2*t + 3*a3*t**2 + 4*a4*t**3 + 5*a5*t**4
    dds = 2*a2 + 6*a3*t + 12*a4*t**2 + 20*a5*t**3

    Q = Q_start + s*(Q_end - Q_start)
    dQ = (Q_end - Q_start)*ds
    ddQ = (Q_end - Q_start)*dds
    
    return (s, Q, dQ, ddQ) if (t <= T) else (s, Q_end, 0, 0)

def cubic_interpol(q0, qd, T, t):
    a0 = 0
    a1 = 0
    a2 = 3/T**2
    a3 = -2/T**3
    s = a3*t**3 + a2*t**2 + a1*t + a0
    ds = 3*a3*t**2 + 2*a2*t + a1
    dds = 6*a3*t + 2*a2
    q = q0 + (qd - q0)*s
    dq = (qd - q0)*ds
    ddq = (qd - q0)*dds
    return (q, dq, ddq) if (t <= T) else (qd, 0, 0)

def feedback_lin(pos, vel, posd, veld, accd):
    u = -kp*(pos - posd) -kv*vel
    ctrl = m*L*L*((g/L)*math.sin(pos)+kf/(m*L*L)*vel + u)
    return ctrl


prev_vel = 0
prev_acc = 0
prev_accd = 0
for t in logTime[1:]:
    if option == 1:
        (posd, veld, accd) = cubic_interpol(q0, qd, T, t)
    if option == 2:
        (s, posd, veld, accd) = fifth_order_poly_profile(q0, qd, T, t)
    if option == 3:
        (s, posd, veld, accd) = trapezoidal_profile(q0, qd, T, t)

    ctrl = feedback_lin(pos, vel, posd, veld, accd)
    logRef[idx] = posd
    logRefd[idx] = veld
    logRefdd[idx] = accd
    logRefddd[idx] = (accd - prev_accd)/dt
    prev_accd = accd
    p.setJointMotorControl2(bodyIndex = bodyId,
                        jointIndex = 1,
                        controlMode = p.TORQUE_CONTROL,
                        force = ctrl)
    p.stepSimulation()
    pos = p.getJointState(bodyId, 1)[0]
    vel = p.getJointState(bodyId, 1)[1]

    acc = (vel - prev_vel)/dt
    prev_vel = vel
    jerk = (acc - prev_acc)/dt
    prev_acc = acc

    logPos[idx] = pos
    logVel[idx] = vel
    logAcc[idx] = acc
    logJerk[idx] = jerk
    logCtr[idx-1] = ctrl
    idx += 1
    if (GUI):
        time.sleep(dt)
    
p.disconnect()

import matplotlib.pyplot as plt
plt.subplot(4,1,1)
plt.grid(True)
plt.plot(logTime, logPos, label = "simPos")
plt.plot(logTime, logRef, label = "simRef")

if option == 1:
    plt.title("Third-order polynomial time scaling")
if option == 2:
    plt.title("Fifth-order polynomial time scaling")
if option == 3:
    plt.title("Trapezoidal motion profile")

plt.legend()

plt.subplot(4,1,2)
plt.grid(True)
plt.plot(logTime, logVel, label = "simVel")
plt.plot(logTime, logRefd, label = "simRefd")
plt.legend()

plt.subplot(4,1,3)
plt.grid(True)
plt.plot(logTime, logAcc, label = "simAcc")
plt.plot(logTime, logRefdd, label = "simRefdd")
plt.legend()

plt.subplot(4,1,4)
plt.grid(True)
plt.plot(logTime, logJerk, label = "simJerk")
plt.plot(logTime, logRefddd, label = "simRefddd")
plt.legend()

plt.show()