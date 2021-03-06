FROM envoyproxy/envoy:v1.14.1

COPY ./envoy.yml /etc/envoy/envoy.yaml

CMD /usr/local/bin/envoy -c /etc/envoy/envoy.yaml -l trace --log-path /tmp/envoy_info.log