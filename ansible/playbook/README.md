# Intro
The goal of this document is to explain in detail every step to be able to deploy on the Raspberry pi zero. Cross-compile has been added on a previous PR that provides an easy way between x86/ARM compilation. With that we can use Ansible to easily compile C++ sources, build the front end and deploy the result on the target. Ansible is obviously optional, every step described here can be one manually.

Ansible has been added to the docker file which means that every tool needed are now included in the image and no external dependency is required.

# Docker
if you haven't done it yet, make sure to build the docker image using the docker-compose.yml file
`docker-compose up --build # inside tools/docker folder`

# connection
Using an other terminal use the following command to get inside the created container:
`docker exec -it laughing-couscous /bin/bash`
try to connect to your Raspberry pi with
`ssh pi@192.X.X.X`
If you can connect then you're good to go for the next steps.

# Install front-end dependencies
This should normally be done already but, , be sure install the front dependencies with
`cd /workspace/laughing-couscous/software/modules/gui/web/ && npm ci`

# Setting the environment before deploying to the target
This step has be done the first time only. It will generate a file with your credential (make sure they are not sooooo secret). Still using the terminal inside the docker, execute the following command with your credentials from ansible/ folder
`ansible-playbook playbook/setup_env.yml --extra-vars "PI_USERNAME=pi PI_IP=192.168.1.6 PI_PORT=22 PI_SSH_PASSWORD=raspberry"`

# Last step, building sources and push the result on the target
`ansible-playbook playbook/build_and_run.yml`

DONE! Now open a browser and enter the Raspberry pi IP address. 
Cheers