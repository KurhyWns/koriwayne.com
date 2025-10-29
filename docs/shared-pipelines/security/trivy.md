# Trivy Vulnerability Scanner

## Overview

Trivy is a comprehensive vulnerability scanner that detects security vulnerabilities in:
- **Dependencies** (npm, pip, go mod, etc.)
- **Container images** (Docker, OCI)
- **File systems** (OS packages, language-specific packages)
- **Infrastructure as Code** (Terraform, Kubernetes, Dockerfile)

## Key Features

- **Multi-language support** - Python, Node.js, Go, Java, Ruby, PHP, Rust, C#
- **Container scanning** - Docker images, OCI artifacts
- **OS package scanning** - Alpine, Ubuntu, Debian, RHEL, CentOS
- **IaC scanning** - Terraform, Kubernetes, Dockerfile, CloudFormation
- **Fast scanning** - Optimized for CI/CD pipelines
- **Multiple output formats** - Table, JSON, SARIF, CycloneDX

## Implementation

**Workflow File**: `shared-pipeline/.github/workflows/lint.yml` (trivy-scan job)

**Key Features**:
- ✅ **File system scanning** - Scans entire repository
- ✅ **Configurable scan paths** - Target specific directories
- ✅ **Table output** - Human-readable results
- ✅ **Exit on vulnerabilities** - Fails build if issues found

## Usage

Add to your project's `.github/workflows/ci.yml`:

```yaml
name: CI Pipeline
on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  lint:
    uses: KurhyWns/shared-pipeline/.github/workflows/lint.yml@main
    with:
      scan-paths: '.'
      fail-on-errors: true
```

## Configuration Options

| Parameter | Description | Default | Type |
|-----------|-------------|---------|------|
| `scan-paths` | Comma-separated paths to scan | `.` | string |
| `fail-on-errors` | Fail workflow if vulnerabilities found | `true` | boolean |

## Supported File Types

Trivy automatically detects and scans:
- **Python**: `requirements.txt`, `Pipfile.lock`, `poetry.lock`
- **Node.js**: `package-lock.json`, `yarn.lock`
- **Go**: `go.mod`, `go.sum`
- **Java**: `pom.xml`, `build.gradle`
- **Ruby**: `Gemfile.lock`
- **PHP**: `composer.lock`
- **Rust**: `Cargo.lock`
- **Docker**: `Dockerfile`, container images
- **Kubernetes**: YAML manifests
- **Terraform**: `.tf` files

## Security Benefits

1. **Dependency vulnerabilities** - Finds known CVEs in dependencies
2. **Container security** - Scans Docker images for vulnerabilities
3. **OS package issues** - Detects vulnerable system packages
4. **IaC misconfigurations** - Finds security issues in infrastructure code
5. **License compliance** - Identifies license issues

## Vulnerability Severity Levels

- **CRITICAL** - Immediate action required
- **HIGH** - Should be addressed soon
- **MEDIUM** - Should be addressed when possible
- **LOW** - Consider addressing
- **UNKNOWN** - Severity not determined

## Integration

The workflow integrates with:
- **GitHub Actions** - Automated execution
- **Pull request checks** - Blocks merges if vulnerabilities found
- **CI/CD pipelines** - Seamless integration
- **Security reporting** - Detailed vulnerability reports

## Best Practices

1. **Run on all branches** - Check vulnerabilities everywhere
2. **Include in CI** - Add to all workflow files
3. **Review findings** - Address critical and high severity issues
4. **Regular updates** - Keep dependencies updated
5. **Baseline management** - Track and manage known issues

## Troubleshooting

**Common Issues**:
- **False positives** - Review and whitelist legitimate issues
- **Performance** - Large repositories may take longer to scan
- **Missing files** - Ensure scan paths include relevant directories

**Debug Mode**:
The workflow provides detailed output showing exactly which files have vulnerabilities and their severity levels.

## Advanced Configuration

For more advanced Trivy configuration, you can:
- **Custom policies** - Define custom security policies
- **Ignore files** - Skip specific files or directories
- **Severity filtering** - Only fail on specific severity levels
- **Output formats** - Generate SARIF, JSON, or other formats
