# Kori Hanes - DevSecOps & GitOps Portfolio

A comprehensive MkDocs-based portfolio showcasing DevSecOps, GitOps practices, and homelab infrastructure configurations.

## Overview

This repository serves as both a professional portfolio and a configuration management system for homelab infrastructure, demonstrating modern DevOps practices including:

- **DevSecOps methodologies** with security-first development
- **GitOps workflows** for reliable deployments
- **Infrastructure as Code** with Docker, Kubernetes, and Terraform
- **Automated security scanning** and quality checks
- **Comprehensive documentation** for all components

## Setup

### Prerequisites
- Python 3.11+
- Git
- Docker (for local development)

### Local Development

1. **Install dependencies**:
```bash
pip install -r requirements.txt
```

2. **Serve locally**:
```bash
mkdocs serve
```

3. **Build for production**:
```bash
mkdocs build
```

4. **Run security checks locally**:
```bash
# Secrets detection
trufflehog filesystem . --only-verified

# Code linting
flake8 .
black --check .
yamllint .

# Docker linting (if Dockerfiles exist)
hadolint **/Dockerfile*
```

## Security & Quality Checks

This repository implements comprehensive security and quality checks that run on every pull request to `develop`:

### 🔒 **Secrets Detection**
- **TruffleHog OSS**: Scans for hardcoded secrets and credentials
- **GitLeaks**: Detects secrets in git history
- **detect-secrets**: Baseline-based secret detection

### 🐍 **Code Quality**
- **Black**: Python code formatting
- **isort**: Import statement sorting
- **Flake8**: Python linting and style checking
- **MyPy**: Static type checking
- **Bandit**: Security linting for Python
- **Safety**: Dependency vulnerability scanning

### 📝 **Documentation**
- **markdownlint**: Markdown file linting
- **yamllint**: YAML file validation
- **MkDocs**: Documentation build testing
- **linkchecker**: Broken link detection

### 🐳 **Infrastructure**
- **Hadolint**: Dockerfile best practices and security
- **kubeval**: Kubernetes manifest validation
- **kube-score**: Kubernetes security and best practices
- **Helm**: Helm chart linting
- **Terraform**: Infrastructure code linting and formatting

## Branching Strategy

This repository follows GitFlow principles with branch protection:

```
main (production)
├── develop (integration)
│   ├── feature/feature-name
│   ├── hotfix/critical-fix
│   └── release/v1.0.0
```

### Workflow
1. **Feature branches** → **develop** (via PR with security checks)
2. **develop** → **main** (via PR with security checks)
3. **Hotfixes** → **main** → **develop** (emergency fixes)

### Branch Protection
- **No direct pushes** to main or develop
- **Required reviews** from code owners
- **Security checks must pass** before merge
- **Status checks required** for all merges

## Adding Content

### New Documentation
1. Create a new `.md` file in `docs/`
2. Add to navigation in `mkdocs.yml`
3. Follow the established structure

### New Projects
1. Create a new `.md` file in `docs/projects/`
2. Add to the Projects section in `mkdocs.yml`
3. Include comprehensive documentation

### Infrastructure Configurations
1. Add Docker, Kubernetes, or Terraform files
2. Follow naming conventions and best practices
3. Include proper documentation and comments
4. Security checks will automatically validate

## Deployment

- **Automatic deployment** to GitHub Pages from main branch
- **Custom domain**: https://koriwayne.com
- **Repository**: https://github.com/KurhyWns/static_site_test

## Security Features

- **Secrets scanning** on every commit
- **Dependency vulnerability** checking
- **Infrastructure security** validation
- **Code quality** enforcement
- **Automated security** reporting

## Contributing

1. **Fork the repository**
2. **Create a feature branch** from develop
3. **Make your changes** following best practices
4. **Run security checks** locally
5. **Create a pull request** to develop
6. **All checks must pass** before merge

## License

This project is open source and available under the [MIT License](LICENSE).
