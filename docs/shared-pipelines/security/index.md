# Security Scanning

## Overview

The shared-pipeline repository provides comprehensive security scanning capabilities to identify vulnerabilities, misconfigurations, and security issues across all projects. This section covers all available security scanning tools and their implementations.

## Available Tools

### 🔍 **Trivy Vulnerability Scanner** ✅ **IMPLEMENTED**
- **Status**: Active and working
- **Purpose**: Scans for vulnerabilities in dependencies, containers, and IaC
- **Coverage**: File systems, container images, infrastructure code
- **Documentation**: [Trivy Details](trivy.md)

### 🛡️ **Secrets Detection** ✅ **IMPLEMENTED**
- **Status**: Active and working
- **Purpose**: Detects hardcoded secrets and credentials
- **Coverage**: Current files and git history
- **Documentation**: [Secrets Detection](../secrets-detection/index.md)

### 🔒 **SAST Scanning** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Static Application Security Testing
- **Coverage**: Source code analysis

### 🐳 **Container Security** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Container image vulnerability scanning
- **Coverage**: Docker images and OCI artifacts

### 🏗️ **Infrastructure Security** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Infrastructure as Code security scanning
- **Coverage**: Terraform, Kubernetes, Dockerfile

## Implementation Strategy

### Current Implementation
- **Trivy** is fully implemented and active
- **Secrets Detection** (TruffleHog + GitLeaks) is fully implemented
- Both run on every push to `main` branch
- Both run on all pull requests to `main`
- Uses shared-pipeline workflow for consistency

### Future Roadmap
1. **SAST scanning** - Semgrep for code analysis
2. **Container scanning** - Enhanced Trivy container scanning
3. **IaC scanning** - Checkov for infrastructure security
4. **License compliance** - FOSSA for license checking
5. **Custom policies** - Project-specific security rules

## Usage

All security scanning tools are available as reusable workflows in the shared-pipeline repository. Projects can include them in their CI/CD pipelines by referencing the appropriate workflow files.

## Security Benefits

- **Vulnerability detection** - Find known security issues early
- **Dependency security** - Ensure secure third-party components
- **Container security** - Secure containerized applications
- **Infrastructure security** - Secure infrastructure configurations
- **Secrets protection** - Prevent credential leaks
- **Compliance** - Meet security standards and regulations
