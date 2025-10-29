# Shared Pipeline Strategy

This document outlines the shared pipeline strategy for managing CI/CD workflows across multiple projects in a DevSecOps environment.

## Overview

The shared pipeline approach follows the DRY (Don't Repeat Yourself) principle by centralizing reusable GitHub Actions workflows in a dedicated repository, ensuring consistency, maintainability, and standardized security practices across all projects.

## Architecture

### **Shared Pipeline Repository Structure**

```
@koriwayne/shared-pipelines/
├── .github/workflows/
│   ├── security-scan.yml      # Comprehensive security checks
│   ├── docker-build.yml       # Docker image building
│   ├── k8s-deploy.yml         # Kubernetes deployment
│   ├── terraform-plan.yml     # Infrastructure validation
│   ├── docs-build.yml         # Documentation building
│   └── release.yml            # Release automation
├── templates/                  # Pipeline templates
│   ├── security-template.yml
│   ├── docker-template.yml
│   └── k8s-template.yml
├── scripts/                    # Shared scripts
│   ├── security-scan.sh
│   ├── docker-build.sh
│   └── k8s-deploy.sh
├── configs/                    # Configuration files
│   ├── .gitleaks.toml
│   ├── .secrets.baseline
│   └── security-policies.yml
└── README.md                   # Usage documentation
```

## Core Workflows

### 1. **Security Scan Workflow**

**File**: `security-scan.yml`

```yaml
name: Security Scan
on:
  workflow_call:
    inputs:
      scan-type:
        description: 'Type of security scan'
        required: false
        default: 'full'
        type: string
      fail-on-high:
        description: 'Fail on high severity issues'
        required: false
        default: 'true'
        type: boolean

jobs:
  secrets-detection:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4
        with:
          fetch-depth: 0
      
      - name: Run TruffleHog OSS
        uses: trufflesecurity/trufflehog@main
        with:
          path: ./
          base: main
          head: HEAD
          extra_args: --debug --only-verified
      
      - name: Run GitLeaks
        uses: gitleaks/gitleaks-action@v2
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      
      - name: Install detect-secrets
        run: pip install detect-secrets
      
      - name: Run detect-secrets
        run: |
          detect-secrets scan --baseline .secrets.baseline
          detect-secrets audit .secrets.baseline
```

### 2. **Docker Build Workflow**

**File**: `docker-build.yml`

```yaml
name: Docker Build
on:
  workflow_call:
    inputs:
      dockerfile:
        description: 'Path to Dockerfile'
        required: true
        type: string
      image-name:
        description: 'Docker image name'
        required: true
        type: string
      registry:
        description: 'Container registry'
        required: false
        default: 'ghcr.io'
        type: string

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4
      
      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3
      
      - name: Run Hadolint
        uses: hadolint/hadolint-action@v3.1.0
        with:
          dockerfile: ${{ inputs.dockerfile }}
          format: sarif
          output-file: hadolint-results.sarif
      
      - name: Build Docker image
        uses: docker/build-push-action@v5
        with:
          context: .
          file: ${{ inputs.dockerfile }}
          push: false
          tags: ${{ inputs.registry }}/${{ inputs.image-name }}:latest
```

### 3. **Kubernetes Deploy Workflow**

**File**: `k8s-deploy.yml`

```yaml
name: Kubernetes Deploy
on:
  workflow_call:
    inputs:
      k8s-files:
        description: 'Path to Kubernetes manifests'
        required: true
        type: string
      namespace:
        description: 'Kubernetes namespace'
        required: false
        default: 'default'
        type: string

jobs:
  validate:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4
      
      - name: Install kubeval
        run: |
          wget https://github.com/instrumenta/kubeval/releases/latest/download/kubeval-linux-amd64.tar.gz
          tar xf kubeval-linux-amd64.tar.gz
          sudo cp kubeval /usr/local/bin
      
      - name: Run kubeval
        run: |
          find ${{ inputs.k8s-files }} -name "*.yaml" -o -name "*.yml" | xargs kubeval
      
      - name: Install kube-score
        run: |
          wget https://github.com/zegl/kube-score/releases/latest/download/kube-score_linux_amd64.tar.gz
          tar xf kube-score_linux_amd64.tar.gz
          sudo cp kube-score /usr/local/bin
      
      - name: Run kube-score
        run: |
          find ${{ inputs.k8s-files }} -name "*.yaml" -o -name "*.yml" | xargs kube-score score
```

### 4. **Terraform Plan Workflow**

**File**: `terraform-plan.yml`

```yaml
name: Terraform Plan
on:
  workflow_call:
    inputs:
      terraform-dir:
        description: 'Terraform directory'
        required: true
        type: string
      workspace:
        description: 'Terraform workspace'
        required: false
        default: 'default'
        type: string

jobs:
  plan:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4
      
      - name: Setup Terraform
        uses: hashicorp/setup-terraform@v3
        with:
          terraform_version: '1.6.0'
      
      - name: Install tflint
        run: |
          curl -s https://raw.githubusercontent.com/terraform-linters/tflint/master/install_linux.sh | bash
      
      - name: Run tflint
        run: |
          cd ${{ inputs.terraform-dir }}
          tflint .
      
      - name: Terraform Format Check
        run: |
          cd ${{ inputs.terraform-dir }}
          terraform fmt -check -diff
      
      - name: Terraform Init
        run: |
          cd ${{ inputs.terraform-dir }}
          terraform init
      
      - name: Terraform Plan
        run: |
          cd ${{ inputs.terraform-dir }}
          terraform plan -out=tfplan
```

## Usage in Projects

### **Referencing Shared Workflows**

In your individual project repositories, reference the shared workflows:

```yaml
# .github/workflows/ci.yml
name: CI Pipeline
on: [push, pull_request]

jobs:
  security:
    uses: koriwayne/shared-pipelines/.github/workflows/security-scan.yml@v1.0.0
    with:
      scan-type: 'full'
      fail-on-high: 'true'
  
  docker-build:
    needs: security
    uses: koriwayne/shared-pipelines/.github/workflows/docker-build.yml@v1.0.0
    with:
      dockerfile: './Dockerfile'
      image-name: 'my-app'
      registry: 'ghcr.io'
  
  k8s-deploy:
    needs: [security, docker-build]
    if: github.ref == 'refs/heads/main'
    uses: koriwayne/shared-pipelines/.github/workflows/k8s-deploy.yml@v1.0.0
    with:
      k8s-files: './k8s'
      namespace: 'production'
```

### **Project-Specific Workflows**

For project-specific needs, create additional workflows:

```yaml
# .github/workflows/project-specific.yml
name: Project Specific
on: [push, pull_request]

jobs:
  # Use shared security scan
  security:
    uses: koriwayne/shared-pipelines/.github/workflows/security-scan.yml@v1.0.0
  
  # Project-specific build steps
  build:
    needs: security
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4
      
      - name: Install dependencies
        run: npm install
      
      - name: Run tests
        run: npm test
      
      - name: Build application
        run: npm run build
```

## Version Management

### **Semantic Versioning**

Tag shared pipeline versions using semantic versioning:

```bash
# Major version for breaking changes
git tag v2.0.0
git push origin v2.0.0

# Minor version for new features
git tag v1.1.0
git push origin v1.1.0

# Patch version for bug fixes
git tag v1.0.1
git push origin v1.0.1
```

### **Version Pinning**

Always pin to specific versions in your project workflows:

```yaml
# ✅ Good - Pinned version
uses: koriwayne/shared-pipelines/.github/workflows/security-scan.yml@v1.0.0

# ❌ Bad - Unpinned version
uses: koriwayne/shared-pipelines/.github/workflows/security-scan.yml@main
```

## Benefits

### **Consistency**
- **Standardized security checks** across all projects
- **Uniform deployment processes** for similar components
- **Consistent code quality** standards

### **Maintainability**
- **Single source of truth** for pipeline logic
- **Centralized updates** and bug fixes
- **Reduced duplication** of pipeline code

### **Scalability**
- **Easy addition** of new projects
- **Reusable components** for different use cases
- **Organization-wide** standards enforcement

### **Security**
- **Centralized security policies** and scanning
- **Consistent vulnerability** management
- **Standardized compliance** checks

## Best Practices

### **1. Version Control**
- Always pin to specific versions
- Use semantic versioning
- Document breaking changes

### **2. Testing**
- Test pipeline changes in development
- Use feature branches for pipeline updates
- Validate with multiple project types

### **3. Documentation**
- Document all inputs and outputs
- Provide usage examples
- Maintain changelog

### **4. Security**
- Keep shared pipelines secure
- Regular security audits
- Access control for pipeline repository

## Migration Strategy

### **Phase 1: Setup**
1. Create shared-pipelines repository
2. Extract common workflows from existing projects
3. Version and tag initial release

### **Phase 2: Adoption**
1. Update one project at a time
2. Test thoroughly before full migration
3. Document any project-specific customizations

### **Phase 3: Optimization**
1. Identify additional common patterns
2. Create more specialized workflows
3. Optimize for performance and reliability

## Tools and Resources

- **GitHub Actions**: Workflow automation
- **Semantic Versioning**: Version management
- **GitHub Releases**: Release management
- **GitHub Packages**: Artifact storage
- **GitHub Security**: Vulnerability scanning

This shared pipeline strategy provides a robust foundation for managing CI/CD workflows across multiple projects while maintaining consistency, security, and maintainability.
