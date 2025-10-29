# TruffleHog OSS

## Overview

TruffleHog OSS is an open-source tool that scans repositories for hardcoded secrets and credentials. It uses advanced pattern matching and entropy analysis to detect various types of secrets including:

- API keys and tokens
- Database credentials
- Private keys
- Passwords and authentication strings
- Cloud service credentials

## Implementation

**Workflow File**: `shared-pipeline/.github/workflows/secrets-detection.yml`

**Key Features**:
- ✅ **Scans entire repository** (not just changed files)
- ✅ **Only verified secrets** (reduces false positives)
- ✅ **Configurable scan paths**
- ✅ **Configurable failure behavior**
- ✅ **GitHub Actions integration**

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
  secrets-detection:
    uses: KurhyWns/shared-pipeline/.github/workflows/secrets-detection.yml@main
    with:
      scan-paths: '.'
      fail-on-secrets: true
```

## Configuration Options

| Parameter | Description | Default | Type |
|-----------|-------------|---------|------|
| `scan-paths` | Comma-separated paths to scan | `.` | string |
| `fail-on-secrets` | Fail workflow if secrets are found | `true` | boolean |

## Security Benefits

1. **Prevents credential leaks** - Catches secrets before they reach production
2. **Reduces false positives** - Only reports verified secrets
3. **Comprehensive scanning** - Scans entire repository, not just changes
4. **Automated enforcement** - Runs on every push and PR
5. **Centralized management** - Single workflow for all projects

## Integration

The workflow integrates with:
- **GitHub Security tab** - Reports findings for review
- **GitHub Actions** - Automated execution
- **Pull request checks** - Blocks merges if secrets found
- **CI/CD pipelines** - Seamless integration

## Best Practices

1. **Run on all branches** - Don't just check main
2. **Fail fast** - Stop builds when secrets are detected
3. **Regular scanning** - Include in all CI workflows
4. **Review findings** - Investigate and remediate quickly
5. **Update patterns** - Keep TruffleHog updated for new secret types

## Troubleshooting

**Common Issues**:
- **False positives** - Review and whitelist legitimate patterns
- **Missing secrets** - Ensure scan paths include all relevant directories
- **Performance** - Large repositories may take longer to scan

**Debug Mode**:
The workflow includes `--debug` flag for detailed output and troubleshooting.
