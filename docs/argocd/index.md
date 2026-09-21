# ArgoCD Documentation

ArgoCD is a declarative, GitOps continuous delivery tool for Kubernetes. This documentation covers installation, configuration, and management of ArgoCD for GitOps workflows.

## Table of Contents

- [Installation](installation.md)
- [Configuration](configuration.md)
- [Application Management](application-management.md)
- [GitOps Workflows](gitops-workflows.md)
- [RBAC and Security](rbac-security.md)
- [Monitoring and Observability](monitoring.md)
- [Troubleshooting](troubleshooting.md)
- [Best Practices](best-practices.md)

## Overview

ArgoCD is a continuous delivery tool that follows the GitOps pattern of using Git repositories as the source of truth for defining the desired application state.

### Key Features

- **Declarative**: Application definitions stored in Git
- **Automated Sync**: Continuous synchronization with Git repositories
- **Multi-Environment**: Support for multiple clusters and environments
- **Web UI**: Intuitive web interface for application management
- **CLI Support**: Command-line interface for automation
- **RBAC**: Role-based access control
- **Multi-Source**: Support for multiple Git repositories

## Architecture

ArgoCD consists of several components:

- **API Server**: REST API and gRPC server
- **Repository Server**: Internal service that maintains Git repository cache
- **Application Controller**: Kubernetes controller that monitors applications
- **Server**: Web UI and API server
- **Redis**: Caching and session storage

## GitOps Principles

ArgoCD implements GitOps by:

1. **Git as Source of Truth**: Application manifests stored in Git
2. **Declarative Configuration**: Desired state defined in Git
3. **Automated Synchronization**: Continuous monitoring and sync
4. **Observability**: Clear visibility into application state

## Quick Start

1. [Install ArgoCD](installation.md)
2. [Access the Web UI](installation.md#access-web-ui)
3. [Create your first application](application-management.md#creating-applications)
4. [Configure Git repositories](configuration.md#repository-configuration)

## Prerequisites

- Kubernetes cluster (v1.19+)
- kubectl configured
- Git repository with application manifests
- RBAC permissions for ArgoCD components
