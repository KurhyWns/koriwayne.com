# Gitea Installation

This guide covers installing Gitea on various platforms and deployment methods.

## Prerequisites

- Linux, macOS, or Windows system
- Git installed
- Database (SQLite, MySQL, PostgreSQL, or MSSQL)
- Minimum 1GB RAM (2GB+ recommended)
- 10GB+ free disk space

## Installation Methods

### Binary Installation

#### Download Gitea

```bash
# Download the latest release
wget -O gitea https://dl.gitea.io/gitea/1.21.0/gitea-1.21.0-linux-amd64
chmod +x gitea
sudo mv gitea /usr/local/bin/
```

#### Create Gitea User

```bash
# Create system user
sudo adduser --system --shell /bin/bash --gecos 'Git Version Control' --group --disabled-password --home /home/git git

# Create directories
sudo mkdir -p /var/lib/gitea/{custom,data,log}
sudo chown -R git:git /var/lib/gitea/
sudo chmod -R 750 /var/lib/gitea/
sudo mkdir /etc/gitea
sudo chown root:git /etc/gitea
sudo chmod 770 /etc/gitea
```

### Docker Installation

#### Using Docker Compose

```yaml
version: "3"

networks:
  gitea:
    external: false

services:
  server:
    image: gitea/gitea:1.21
    container_name: gitea
    environment:
      - USER_UID=1000
      - USER_GID=1000
      - GITEA__database__DB_TYPE=mysql
      - GITEA__database__HOST=db:3306
      - GITEA__database__NAME=gitea
      - GITEA__database__USER=gitea
      - GITEA__database__PASSWD=gitea
    restart: always
    networks:
      - gitea
    volumes:
      - ./gitea:/data
      - /etc/timezone:/etc/timezone:ro
      - /etc/localtime:/etc/localtime:ro
    ports:
      - "3000:3000"
      - "222:22"
    depends_on:
      - db

  db:
    image: mysql:8
    restart: always
    environment:
      - MYSQL_ROOT_PASSWORD=gitea
      - MYSQL_USER=gitea
      - MYSQL_PASSWORD=gitea
      - MYSQL_DATABASE=gitea
    volumes:
      - ./mysql:/var/lib/mysql
    networks:
      - gitea
```

### Kubernetes Installation

#### Using Helm

```bash
# Add Gitea Helm repository
helm repo add gitea-charts https://dl.gitea.io/charts/
helm repo update

# Install Gitea
helm install gitea gitea-charts/gitea
```

## First Run

1. Start Gitea:
   ```bash
   sudo -u git gitea web
   ```

2. Open your browser and navigate to `http://localhost:3000`

3. Complete the installation wizard:
   - Database configuration
   - General settings
   - Admin account creation

## Systemd Service

Create a systemd service for automatic startup:

```ini
[Unit]
Description=Gitea (Git with a cup of tea)
After=syslog.target
After=network.target

[Service]
RestartSec=2s
Type=simple
User=git
Group=git
WorkingDirectory=/var/lib/gitea/
ExecStart=/usr/local/bin/gitea web --config /etc/gitea/app.ini
Restart=always
Environment=USER=git HOME=/home/git GITEA_WORK_DIR=/var/lib/gitea

[Install]
WantedBy=multi-user.target
```

Enable and start the service:

```bash
sudo systemctl enable gitea
sudo systemctl start gitea
```

## Verification

Check if Gitea is running:

```bash
# Check service status
sudo systemctl status gitea

# Check if port is listening
sudo netstat -tlnp | grep :3000

# Test web interface
curl http://localhost:3000
```
