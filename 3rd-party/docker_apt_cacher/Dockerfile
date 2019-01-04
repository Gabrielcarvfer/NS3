#
# Build: docker build -t apt_cacher .
# Run: docker run -d -p 3142:3142 --name apt-cacher apt_cacher
#
# and then you can run containers with:
#   docker run -t -i --rm -e http_proxy http://dockerhost:3142/ debian bash
#                or using the following on their Dockerfile
#   RUN  echo 'Acquire::http { Proxy "http://dockerhost:3142"; };' >> /etc/apt/apt.conf.d/01proxy
#
# Here, `dockerhost` is the IP address or FQDN of a host running the Docker daemon
# which acts as an APT proxy server.
FROM        ubuntu:18.10

VOLUME      ["/var/cache/apt-cacher-ng"]
RUN     apt update && apt install -y apt-cacher-ng

EXPOSE      3142
CMD     chmod -R 777 /var/cache/apt-cacher-ng && chown root:root /var/cache/apt-cacher-ng && /etc/init.d/apt-cacher-ng start && tail -f /var/log/apt-cacher-ng/*