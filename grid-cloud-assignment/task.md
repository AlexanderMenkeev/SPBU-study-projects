# About
This application is the assignment 1 for the Grid and Cloud Computing course.

# How to start
After you have cloned this repository run the following command:
```
docker-compose up
```

# How to test
Client application runs on this port: http://localhost:3000

Server runs on this port: http://localhost:5000

You will need to open JavaScript Console in your browser to test this application.

- The `random` button generates random number which is then send to the backend for saving in the postgres database.
- The `get numbers` button gets all entries from the database and prints them in the console.
- The `reset` button deletes all entries in the database.
