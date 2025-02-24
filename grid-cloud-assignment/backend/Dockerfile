FROM node:latest

WORKDIR /backend/app

COPY package*.json ./

RUN npm install

COPY . .

CMD ["npm", "start"]
