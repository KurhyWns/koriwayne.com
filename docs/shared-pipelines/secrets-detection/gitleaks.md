# GitLeaks

## Overview

GitLeaks is a fast, lightweight tool that scans git repositories for secrets and sensitive information. It analyzes git history to detect secrets that may have been committed in the past, even if they were later removed from the current codebase.

## Key Features

- **Git history scanning** - Analyzes all commits in the repository
- **Fast performance** - Optimized for large repositories
- **Comprehensive detection** - Supports 100+ secret types
- **Configurable rules** - Custom patterns and allowlists
- **GitHub integration** - Native GitHub Actions support

## Implementation

**Workflow File**: `shared-pipeline/.github/workflows/gitleaks.yml`

**Key Features**:
- ✅ **Scans entire git history** (all commits)
- ✅ **Configurable scan paths**
- ✅ **Configurable failure behavior**
- ✅ **GitHub Actions integration**
- ✅ **Fast execution**

## Usage

Add to your project's `.github/workflows/ci.yml`:

```yaml
name: CI Pipeline
on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

permissions:
  contents: read
  security-events: write

jobs:
  gitleaks-detection:
    uses: KurhyWns/shared-pipeline/.github/workflows/gitleaks.yml@main
    with:
      scan-paths: '.'
      fail-on-secrets: true
```

## Configuration Options

| Parameter | Description | Default | Type |
|-----------|-------------|---------|------|
| `scan-paths` | Comma-separated paths to scan | `.` | string |
| `fail-on-secrets` | Fail workflow if secrets are found | `true` | boolean |

## Supported Secret Types

GitLeaks can detect over 100 different types of secrets including:

- **API Keys**: AWS, Google Cloud, Azure, GitHub, etc.
- **Database Credentials**: Connection strings, passwords
- **Private Keys**: SSH, RSA, DSA, ECDSA keys
- **Tokens**: JWT, OAuth, access tokens
- **Cloud Credentials**: Service account keys, certificates
- **Generic Secrets**: Passwords, API keys, tokens

## Security Benefits

1. **Historical analysis** - Finds secrets in git history
2. **Fast scanning** - Quick execution on large repositories
3. **Comprehensive coverage** - 100+ secret types supported
4. **Git integration** - Native git repository analysis
5. **Configurable rules** - Custom patterns and allowlists

## Integration

The workflow integrates with:
- **GitHub Security tab** - Reports findings for review
- **GitHub Actions** - Automated execution
- **Pull request checks** - Blocks merges if secrets found
- **CI/CD pipelines** - Seamless integration

## Best Practices

1. **Run on all branches** - Check historical commits
2. **Regular scanning** - Include in all CI workflows
3. **Review findings** - Investigate and remediate quickly
4. **Custom rules** - Add project-specific patterns
5. **Allowlist management** - Whitelist legitimate patterns

## Troubleshooting

**Common Issues**:
- **False positives** - Review and whitelist legitimate patterns
- **Performance** - Large repositories may take longer to scan
- **Missing secrets** - Ensure scan paths include all relevant directories

**Configuration**:
GitLeaks can be configured with custom rules and allowlists through configuration files in your repository.

## Comparison with TruffleHog

| Feature | GitLeaks | TruffleHog |
|---------|----------|------------|
| **Scope** | Git history | Current files |
| **Speed** | Fast | Moderate |
| **Secret Types** | 100+ | 50+ |
| **Verification** | Pattern-based | Entropy + verification |
| **Use Case** | Historical analysis | Current state scanning |
