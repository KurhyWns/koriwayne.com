# Gitea Documentation

Gitea is a self-hosted Git service that provides a lightweight alternative to GitHub, GitLab, and Bitbucket. This documentation covers installation, configuration, and management of Gitea in a self-hosted environment.

## Table of Contents

- [Installation](installation.md)
- [Configuration](configuration.md)
- [User Management](user-management.md)
- [Repository Management](repository-management.md)
- [Backup and Recovery](backup-recovery.md)
- [Security Best Practices](security.md)
- [Troubleshooting](troubleshooting.md)

## Overview

Gitea is designed to be a painless self-hosted Git service. It's built with Go and can be compiled to a single binary, making it easy to deploy and maintain.

### Key Features

- **Lightweight**: Minimal resource requirements
- **Self-hosted**: Complete control over your Git repositories
- **Web Interface**: Modern, responsive web UI
- **API**: Full REST API for integration
- **Multi-platform**: Runs on Linux, macOS, and Windows
- **Database Support**: SQLite, MySQL, PostgreSQL, and MSSQL

## Quick Start

1. [Download Gitea](installation.md#download)
2. [Configure your environment](configuration.md#environment-setup)
3. [Run the installation wizard](installation.md#first-run)
4. [Create your first repository](repository-management.md#creating-repositories)

## Architecture

Gitea follows a modular architecture with clear separation of concerns:

- **Web Server**: Handles HTTP requests and serves the web interface
- **Git Engine**: Manages Git operations and repository access
- **Database Layer**: Stores metadata, users, and configuration
- **Storage Backend**: Manages file storage and repository data
