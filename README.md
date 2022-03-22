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
3. In /mobile, `expo start`
4. In your phone install expo and read the QR code shown in terminal. Optionally, write `w` to open the app in browser.
