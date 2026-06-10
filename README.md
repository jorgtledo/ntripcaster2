# NtripCaster 2 Dockerized Distribution

This repository packages the BKG Professional NtripCaster 2.x server for containerized deployment and local operation. It includes the upstream source tree, configuration templates, a Docker image, a Compose definition, and the customized web interface assets shipped in this workspace.

NtripCaster is a GNSS data server that implements NTRIP 2 and is designed to handle multiple incoming streams and large numbers of simultaneous clients. In addition to the original upstream functionality, this repository includes recent UI and usability updates reflected in the bundled templates and changelog.

## Contents

- [Overview](#overview)
- [Features](#features)
- [Repository Layout](#repository-layout)
- [Quick Start with Docker Compose](#quick-start-with-docker-compose)
- [Run with Docker Only](#run-with-docker-only)
- [Build from Source](#build-from-source)
- [Configuration](#configuration)
- [Web UI and Administration](#web-ui-and-administration)
- [Recent Changes](#recent-changes)
- [Selected Historical Changes](#selected-historical-changes)
- [Notes and Caveats](#notes-and-caveats)
- [References](#references)
- [License](#license)

## Overview

This project is a practical distribution of NtripCaster focused on straightforward deployment.

It provides:

- A multi-stage Docker build based on Ubuntu 24.04.
- A Compose file with mounted configuration and log directories.
- The upstream BKG Professional NtripCaster source code and documentation.
- Ready-to-copy configuration templates for users, groups, mount authorization, sourcetable, and main server settings.
- A customized HTML admin/home interface with language resources.

## Features

Verified from the source tree, bundled manual, and changelog:

- NTRIP 2 support with HTTP-compatible communication.
- Backward-compatible NTRIP 1 source upload support.
- Sourcetable delivery and sourcetable filtering via request path.
- Relay support for pulling remote streams into the local caster.
- Direct pull relay without NTRIP protocol for raw stream endpoints.
- Relay support for NTRIP 2, HTTP/1.1, TLS, and HTTP proxying.
- Optional RTSP, RTP, TCP chunked transfer, and UDP-related functionality in the upstream codebase.
- User-based authentication and authorization for clients and sources.
- Group-based access control and connection restrictions.
- IP-based ACL rules and explicit banlist support.
- Prometheus metrics exposure.
- Telnet-based administration and browser-based admin UI.
- Multi-instance operation from a single installation.
- systemd integration and watchdog support upstream.
- Localized web interface resources in English, Spanish, and German.
- Customized web UI, language selection, hidden server version, removed favicon, and client IP blocking/ban improvements in recent revisions.

## Repository Layout

Top-level structure:

- `Dockerfile`: multi-stage image build for NtripCaster.
- `docker-compose.yml`: container runtime definition with mounted config and logs.
- `conf/`: runtime configuration mounted into the container. This folder is initially empty and should contain your active config files.
- `logs/`: runtime logs mounted from the container. This folder is initially empty.
- `ntripcaster/`: upstream source tree, templates, scripts, config templates, and bundled documentation.

Important subdirectories inside `ntripcaster/`:

- `conf/`: distribution template files such as `*.dist` and `*.aut.dist`.
- `src/`: upstream C source code.
- `scripts/`: startup scripts and systemd service files.
- `templates/`: HTML templates and translation JSON files.

## Quick Start with Docker Compose

### 1. Create the runtime configuration files

Copy the distributed templates from `ntripcaster/conf/` into the top-level `conf/` directory used by Docker Compose.

On Linux or macOS:

```bash
cp ./ntripcaster/conf/users.aut.dist ./conf/users.aut
cp ./ntripcaster/conf/groups.aut.dist ./conf/groups.aut
cp ./ntripcaster/conf/clientmounts.aut.dist ./conf/clientmounts.aut
cp ./ntripcaster/conf/sourcemounts.aut.dist ./conf/sourcemounts.aut
cp ./ntripcaster/conf/sourcetable.dat.dist ./conf/sourcetable.dat
cp ./ntripcaster/conf/ntripcaster.conf.dist ./conf/ntripcaster.conf
cp ./ntripcaster/conf/banlist.conf.dist ./conf/banlist.conf
```

On Windows PowerShell:

```powershell
Copy-Item .\ntripcaster\conf\users.aut.dist .\conf\users.aut
Copy-Item .\ntripcaster\conf\groups.aut.dist .\conf\groups.aut
Copy-Item .\ntripcaster\conf\clientmounts.aut.dist .\conf\clientmounts.aut
Copy-Item .\ntripcaster\conf\sourcemounts.aut.dist .\conf\sourcemounts.aut
Copy-Item .\ntripcaster\conf\sourcetable.dat.dist .\conf\sourcetable.dat
Copy-Item .\ntripcaster\conf\ntripcaster.conf.dist .\conf\ntripcaster.conf
Copy-Item .\ntripcaster\conf\banlist.conf.dist .\conf\banlist.conf
```

### 2. Edit the configuration

At minimum, review and adjust:

- `conf/ntripcaster.conf`
- `conf/users.aut`
- `conf/groups.aut`
- `conf/clientmounts.aut`
- `conf/sourcemounts.aut`
- `conf/sourcetable.dat`
- `conf/banlist.conf`

Recommended first changes:

- Set a valid `server_name`.
- Choose the ports you want to expose.
- Replace default admin, operator, and encoder passwords.
- Update caster metadata such as `name`, `location`, `url`, `operator`, and `rp_email`.
- Review `language`, ACL settings, and logging paths.

### 3. Start the service

```bash
docker compose up -d
```

### 4. Access the caster

If you are running locally with the default published port, the main endpoints are:

- Sourcetable: `http://localhost:2101/`
- Home page: `http://localhost:2101/home`
- Admin UI: `http://localhost:2101/admin`

### 5. Stop the service

```bash
docker compose down
```

## Run with Docker Only

Build the image manually:

```bash
docker build -t ntripcaster2 .
```

Run the container with mounted configuration and logs:

```bash
docker run \
	-v "${PWD}/conf:/usr/local/ntripcaster/conf" \
	-v "${PWD}/logs:/usr/local/ntripcaster/logs" \
	-p 2101:2101 \
	--rm \
	--name ntripcaster2 \
	-d ntripcaster2
```

On Windows PowerShell, use:

```powershell
docker run `
	-v "${PWD}\conf:/usr/local/ntripcaster/conf" `
	-v "${PWD}\logs:/usr/local/ntripcaster/logs" `
	-p 2101:2101 `
	--rm `
	--name ntripcaster2 `
	-d ntripcaster2
```

## Build from Source

The upstream project uses Autotools.

Typical dependencies on Ubuntu 24.04:

- `autoconf`
- `build-essential`
- `dos2unix`

Build steps:

```bash
cd ntripcaster
autoreconf -fiv
./configure
make
make install
```

The default upstream installation prefix is `/usr/local/ntripcaster` unless you pass a different `--prefix` value to `./configure`.

The upstream documentation also mentions:

- `--enable-fsstd` for filesystem-standard installation paths.
- `--with-libwrap` for tcp wrapper support.
- `--with-crypt` for encrypted passwords.
- `--without-readline` if readline support is not desired.

## Configuration

The main runtime configuration file is `conf/ntripcaster.conf` in containerized deployments.

Key settings exposed by the distributed template include:

- Server metadata: `location`, `name`, `url`, `operator`, `operator_url`, `rp_email`
- Capacity and throttling: `max_clients`, `max_sources`, `max_admins`, `throttle`
- Per-IP connection limiting: `max_ip_connections`
- Authentication: `encoder_password`, `admin_password`, `oper_password`
- Network binding: `server_name`, `port`
- Aliases: `alias /old /new`
- Relay definitions: `relay pull ...`
- Sourcetable file selection: `sourcetablefile`
- Logging and runtime files: `logfilename`, `usagefilename`, `logdir`, `watchfilename`, `pidfilename`
- Templates location: `templatedir`
- UI language: `language en|es|de`
- Reverse lookups: `reverse_lookups`
- ACL policy: `acl_policy`
- LDAP parameters: `ldap_server`, `ldap_uid_prefix`, `ldap_people_context`
- Security options: `read_timeout`, `sourcetable_via_udp`, `hide_version`
- Banlist file: `banlistfile`

Authentication and authorization files:

- `users.aut`: user credentials.
- `groups.aut`: group definitions and limits.
- `clientmounts.aut`: client access to mountpoints.
- `sourcemounts.aut`: source upload authorization.
- `banlist.conf`: blocked or banned client definitions.
- `sourcetable.dat`: published stream metadata.

## Web UI and Administration

This repository includes the upstream web interface templates plus recent customizations.

Available HTTP endpoints:

- `/` for sourcetable access.
- `/home` for the public home page.
- `/admin` for the password-protected administration interface.

Administrative capabilities documented upstream and reflected in the repository include:

- Web-based server administration.
- Local admin console usage through the startup script when not backgrounded.
- Telnet-style administrative access using operator and admin credentials.
- Connection management, including kicking clients and recent IP block/ban support.

Language resources are available in:

- `ntripcaster/templates/lang/en.json`
- `ntripcaster/templates/lang/es.json`
- `ntripcaster/templates/lang/de.json`

## Recent Changes

Recent changes recorded in `ntripcaster/CHANGES` and reflected in this repository:

### 2.0.47 to 2.0.48

- New UI.
- Language selection.

### 2.0.46 to 2.0.47

- Hide server version.
- Remove favicon.
- Block and ban IP clients.

### 2.0.45 to 2.0.46

- Extended Prometheus statistics.

### 2.0.44 to 2.0.45

- Cross-site scripting issue fixed: CVE-2023-3034.
- Fixed relay behavior that could drop active NTRIP 2 connections.

## Selected Historical Changes

Notable upstream capabilities added over time:

- Prometheus statistics export.
- TLS relay pull support for NTRIP 2.
- systemd unit support and watchdog integration.
- CORS header support for easier JavaScript-based access to HTTP/NTRIP 2 endpoints.
- HTTP proxy support for relay connections.
- Sourcetable over UDP control disabled by default for security.
- LDAP authentication support.
- Multi-instance installation support.
- RTSP, RTP, UDP, and chunked transfer support introduced in the NTRIP 2 series.

## Notes and Caveats

Current repository-specific operational notes derived from the Dockerfile and bundled scripts:

- The Compose setup mounts the top-level `conf/` and `logs/` directories into the container, so active runtime configuration should live there, not inside `ntripcaster/conf/`.
- The Docker image exposes port `2101` by default, but additional ports can be configured in `ntripcaster.conf` and published separately if needed.
- The image starts the upstream `ntripcaster` script. The Dockerfile documents that the startup script may exit with code `1`, so the container command keeps the container alive afterward.
- The Dockerfile also notes that regular service logs are not fully redirected to stdout; mounted log files under `logs/` remain the primary place to inspect runtime output.
- The upstream manual warns against editing configuration files with tools that introduce incompatible line endings. In this repository, the Docker build normalizes source and config text files with `dos2unix` during image build.

## References

- Upstream quick documentation: `ntripcaster/README`
- Upstream installation notes: `ntripcaster/INSTALL`
- Full operations manual: `ntripcaster/ntripcaster_manual.html`
- Upstream change log: `ntripcaster/CHANGES`

## License

NtripCaster is distributed under the GNU General Public License version 3. See the repository `LICENSE` file and the upstream licensing files bundled in `ntripcaster/` for details.
