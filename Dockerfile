FROM ubuntu:24.04 AS builder

COPY ntripcaster /ntripcaster

WORKDIR /ntripcaster

RUN apt-get update && \
    apt-get install -y autoconf build-essential dos2unix

RUN find . -type f \( -name "*.ac" -o -name "*.am" -o -name "*.in" -o -name "configure*" -o -name "Makefile*" -o -name "*.c" -o -name "*.h" -o -name "*.sh" -o -name "casterwatch" -o -name "ntripcaster" -o -name "*.conf*" -o -name "*.aut*" -o -name "*.dat*" \) -exec dos2unix {} + 2>/dev/null || true

RUN autoreconf -fiv && ./configure && make && make install

# Create a minimal image which only contains the built binaries
FROM ubuntu:24.04

RUN apt-get update && apt-get install -y --no-install-recommends bash && rm -rf /var/lib/apt/lists/*

# Note that the ./configure script installs into /usr/local/ntripcaster
# by default.
COPY --from=builder /usr/local/ntripcaster/ /usr/local/ntripcaster/

# Set the working directory to the log directory for easy access
# to the log files via `docker exec cat <log-name>.log`
WORKDIR /usr/local/ntripcaster/logs

# This is the default port the caster will listen on, but it can 
# be changed by editing /usr/local/ntripcaster/conf/ntripcaster.conf
EXPOSE 2101

# Note 1: The default startup script always exits with exit code 1 due 
# to a bug in the ntripcaster script.
# Note 2: no logs apart from startup logs are currently output to stdout.
# Note 3: setting the console_mode to 0/1/2 in ntripcaster.conf has no effect
# as the casterwatch script passes "-b" to the ntripdaemon (see line 18) 
# which sets info.console_mode equal to CONSOLE_BACKGROUND (after parsing 
# the config file) which is equivalent to setting console_mode to 3.
CMD /usr/local/ntripcaster/bin/ntripcaster start || echo "Failed: $?" && sleep infinity
