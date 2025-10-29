# Linting

## Overview

The shared-pipeline repository provides comprehensive linting capabilities to ensure code quality, consistency, and adherence to best practices across all projects. This section covers all available linting tools and their implementations.

## Available Tools

### 📝 **YAML Lint** ✅ **IMPLEMENTED**
- **Status**: Active and working
- **Purpose**: Validates YAML syntax and formatting
- **Coverage**: YAML files across the repository
- **Documentation**: [YAML Lint Details](yaml-lint.md)

**Combined Workflow**: All linting tools run together in a single `lint.yml` workflow

### 🐍 **Python Lint** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Python code quality and style checking
- **Coverage**: Python files with multiple linters

### 📄 **Markdown Lint** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Markdown file formatting and style
- **Coverage**: Documentation and README files

### 🐳 **Docker Lint** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Dockerfile best practices and security
- **Coverage**: Docker and containerization files

### ☸️ **Kubernetes Lint** 📋 **PLANNED**
- **Status**: Planned for future implementation
- **Purpose**: Kubernetes manifest validation
- **Coverage**: YAML manifests and Helm charts

## Implementation Strategy

### Current Implementation
- **YAML Lint** is fully implemented and active
- Runs on every push to `main` branch
- Runs on all pull requests to `main`
- Uses shared-pipeline workflow for consistency

### Future Roadmap
1. **Python linting** - Black, isort, flake8, mypy
2. **Markdown linting** - markdownlint for documentation
3. **Docker linting** - Hadolint for Dockerfiles
4. **Kubernetes linting** - kubeval, kube-score for manifests
5. **Terraform linting** - tflint, terraform fmt for IaC

## Usage

All linting tools are available as reusable workflows in the shared-pipeline repository. Projects can include them in their CI/CD pipelines by referencing the appropriate workflow files.

## Quality Benefits

- **Consistent formatting** across all file types
- **Early error detection** before deployment
- **Best practices enforcement** automatically
- **Code quality standards** maintained
- **Reduced technical debt** through automated checks
