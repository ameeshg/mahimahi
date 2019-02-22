This is a mahimahi fork that allows for HTTP2 push.


INSTALLATION

To install correctly, you need openssl 1.0.2 or higher, and nghttp2 1.14.1 or higher.

If you do upgrade your openssl, the nghttp2 install may not pick up on the upgraded version. To point to the upgraded version of openssl during the nghttp2 install, point to openssl's package config, as follows:

`./configure PKG_CONFIG_PATH=/usr/local/ssl/lib/pkgconfig`

USAGE

To record a site, run `mm-webrecord [directory_name]`. Inside the shell, run `google-chrome --ignore-certificate-errors` and load the target site. Exit the shell and your site will be recorded.

Add link headers in the `replayserver.cc` file by following the "apple.com" example already listed.

To replay the site, run:
`mm-proxyreplay ~/[directory_name]/ /usr/local/bin/nghttpx /home/[username]/mahimahi/src/frontend/certs/reverse_proxy_key.pem /home/[username]/mahimahi/src/frontend/certs/reverse_proxy_cert.pem`

Then inside the shell run:
`google-chrome --ignore-certificate-errors --proxy-pac-url=/home/username/config_testing.pac`

DEBUGGING:
nghttp logs are in `~/error-logs/`
apache logs are in `/tmp/`

