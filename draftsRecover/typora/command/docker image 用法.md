docker pull image_name

docker run -it --net=host --name = yourmirror_name image_name /bin/bash

useradd --create-home fan

passwd fan

usermod -d /home/fan -m fan

usermod -aG root fan

gpasswd -a fan wheel

