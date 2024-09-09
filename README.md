# Installation

## Docker

Create the six NTRIP caster configuration files (`users.aut`, `groups.aut`, `clientmounts.aut`, `sourcemounts.aut`, `sourcetable.dat` and `ntripcaster.conf`) using the commands below

```bash 
cp ./ntripcaster/conf/users.aut.dist ./ntripcaster/conf/users.aut
cp ./ntripcaster/conf/groups.aut.dist ./ntripcaster/conf/groups.aut
cp ./ntripcaster/conf/clientmounts.aut.dist ./ntripcaster/conf/clientmounts.aut
cp ./ntripcaster/conf/sourcemounts.aut.dist ./ntripcaster/conf/sourcemounts.aut
cp ./ntripcaster/conf/sourcetable.dat.dist ./ntripcaster/conf/sourcetable.dat
cp ./ntripcaster/conf/ntripcaster.conf.dist ./ntripcaster/conf/ntripcaster.con
```
Modify the configuration files using your favourite text editor and then run
```
docker compose up -d
```

or

```bash
docker build -t ntripcaster2 . 
docker run -v ./ntripcaster/conf:/usr/local/ntripcaster/conf -p 2101:2101 --rm --name ntripcaster2 -dit ntripcaster2
```

If running docker on your local computer, you should now be able to use your computer's browser to access the caster's sourcetable, homepage, and admin Web UI at http://localhost:2101, http://localhost:2101/home, and http://localhost:2101/admin.

Refer to `./ntripcaster/ntripcaster_manual.html` for more information.
