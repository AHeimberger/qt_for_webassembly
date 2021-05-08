#/bin/bash

PROJECT_NAME="qt_project"
DIR_DEPLOY="${HOME}/deploy/${PROJECT_NAME}"
mkdir -p "${DIR_DEPLOY}"

docker build \
    -t ${PROJECT_NAME} \
    --build-arg GROUP_ID=$(id -g ${USER}) \
    --build-arg USER_ID=$(id -u ${USER}) \
    --build-arg USER_NAME=${USER} \
     .

docker run \
    --rm \
    --volume="${DIR_DEPLOY}:/deploy/" \
    -it ${PROJECT_NAME} \
    /bin/bash
