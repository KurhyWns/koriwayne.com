# Secrets Detection

## Overview

The shared-pipeline repository provides comprehensive secrets detection capabilities to prevent sensitive information from being accidentally committed to repositories. This section covers all available secrets detection tools and their implementations.

## Available Tools

### 🔒 **TruffleHog OSS** ✅ **IMPLEMENTED**
- **Status**: Active and working
- **Purpose**: Scans for hardcoded secrets and credentials
- **Coverage**: Current files scanning
- **Documentation**: [TruffleHog Details](trufflehog.md)

### 🔍 **GitLeaks** ✅ **IMPLEMENTED**
- **Status**: Active and working
- **Purpose**: Detects secrets in git history
- **Coverage**: Historical commit analysis
- **Documentation**: [GitLeaks Details](gitleaks.md)

**Combined Workflow**: Both tools run together in a single `secrets-detection.yml` workflow

### 🛡️ **detect-secrets** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Baseline-based secret detection
- **Coverage**: Incremental scanning with baselines

## Implementation Strategy

### Current Implementation
- **TruffleHog OSS** is fully implemented and active
- Runs on every push to `main` branch
- Runs on all pull requests to `main`
- Uses shared-pipeline workflow for consistency

### Future Roadmap
1. **GitLeaks integration** - Historical secret detection
2. **detect-secrets integration** - Baseline-based scanning
3. **Custom rules** - Project-specific secret patterns
4. **Reporting dashboard** - Centralized findings management

## Usage

All secrets detection tools are available as reusable workflows in the shared-pipeline repository. Projects can include them in their CI/CD pipelines by referencing the appropriate workflow files.

## Security Benefits

- **Prevents credential leaks** before they reach production
- **Comprehensive coverage** across multiple detection methods
- **Automated enforcement** in CI/CD pipelines
- **Centralized management** through shared workflows
- **Consistent standards** across all projects
