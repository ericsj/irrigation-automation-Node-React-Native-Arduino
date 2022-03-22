<h1>Irrigation automation using Arduino, Node.js, and React Native</h1>

<h2>About</h2>
This system is composed of three modules:

1. An Arduino Uno device and some electronic components. The Arduino runs the c++ code contained in the file iot.cpp. This script checks irrigation moisture frequently and activates a relay for allowing irrigation during a determined time. After irrigation, it sends system status data to the API. Check components and electronics <a href='https://www.circuito.io/app?components=9442,9590,9591,11021,13322,13678,3061987'>here</a>.
2. An API developed using Node.Js and Sequelize ORM. It allows CRUD operations to handle irrigation data.
3. A mobile frontend built with React Native and Expo. The purpose of the mobile is to monitor if the irrigation is working and display the cause of a potential failure.

<h2>Screenshots</h2>
<h3>Mobile</h3>

![ok](https://user-images.githubusercontent.com/47046552/166389949-7eec0d3f-d7c9-4ee9-89b3-79634f034833.png)![fail](https://user-images.githubusercontent.com/47046552/166390902-15d63c71-7b0a-48bc-8181-4b851aac9ff4.png)

<h3>Electronic circuit</h3>

![eletro](https://user-images.githubusercontent.com/47046552/166392074-3f4fc725-3e38-48ad-be42-0b538b0c9bf4.png)

<h2>How to run the project</h2>

1. Setup hardware project and deploy iot.cpp in the Arduino (optional)
2. install backend dependencies and start backend
3. Turn on Arduino (or send mock data with Postman)
4. install .apk and Start mobile app (or use Expo app)

<h3>How to setup backend</h3>

1. Install Postgres: `sudo apt install postgresql`
2. Start Postgres: `services start postgresql`
3. Go to /backend/config/database.js and make sure your postgres configs are correct
4. Go to /backend and run `npm i`
5. In /backend, run `npm start`
6. If everything is ok, you should see SQL queries and logs in the terminal

<h3>How to setup mobile</h3>

1. You can run the project in your browser or cellphone without installing the apk. First, install Expo `npm i -g expo-cli`
2. Go to /mobile and run `npm i`
3. In /mobile, `expo start:web`. A preview of the app will open in your browser
4. On your phone install expo and read the QR code shown in terminal.
