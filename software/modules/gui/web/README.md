### 'Running the app'

- If it's the first time, the nodejs packages must be installed. For that go to ./laughing-couscous/software/modules/gui/web and run 'npm ci'
- Make sure cpp web_server_exe is running using cmake. This will also generate cpp classes for gRPC
- in the same folder gui/web run the command 'npm start'

### `npm start`

Runs the app in the development mode.<br />
Before starting, gRPC will generate every required typescript classes
Open [http://localhost:3000](http://localhost:3000) to view it in the browser.

The page will reload if you make edits.<br />
You will also see any lint errors in the console.
