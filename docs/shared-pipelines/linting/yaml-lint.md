# YAML Lint

## Overview

YAML Lint is a tool that validates YAML syntax and enforces consistent formatting across YAML files. It helps ensure that configuration files, GitHub Actions workflows, and other YAML documents are properly formatted and follow best practices.

## Key Features

- **Syntax validation** - Catches YAML syntax errors
- **Formatting consistency** - Enforces consistent indentation and style
- **Best practices** - Validates against YAML standards
- **Configurable rules** - Custom linting rules and exceptions
- **Multiple file support** - Scans all YAML files in specified paths

## Implementation

**Workflow File**: `shared-pipeline/.github/workflows/lint.yml` (yaml-lint job)

**Key Features**:
- ✅ **Scans specified paths** for YAML files
- ✅ **Configurable failure behavior**
- ✅ **Parsable output** for CI integration
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
| `scan-paths` | Comma-separated paths to scan for YAML files | `.` | string |
| `fail-on-errors` | Fail workflow if linting errors are found | `true` | boolean |

## Supported File Types

YAML Lint validates:
- **GitHub Actions workflows** (`.github/workflows/*.yml`)
- **Configuration files** (`*.yml`, `*.yaml`)
- **Kubernetes manifests** (`*.yml`, `*.yaml`)
- **Docker Compose files** (`docker-compose.yml`)
- **MkDocs configuration** (`mkdocs.yml`)
- **CI/CD configurations** (`.gitlab-ci.yml`, etc.)

## Quality Benefits

1. **Syntax validation** - Catches YAML errors before deployment
2. **Consistent formatting** - Enforces uniform style across files
3. **Best practices** - Validates against YAML standards
4. **Early detection** - Finds issues in CI before they cause problems
5. **Team consistency** - Ensures all team members follow same standards

## Integration

The workflow integrates with:
- **GitHub Actions** - Automated execution
- **Pull request checks** - Blocks merges if errors found
- **CI/CD pipelines** - Seamless integration
- **Code review** - Provides detailed error reports

## Best Practices

1. **Run on all branches** - Check YAML files everywhere
2. **Include in CI** - Add to all workflow files
3. **Review errors** - Fix linting issues promptly
4. **Custom rules** - Configure project-specific rules
5. **Regular updates** - Keep yamllint updated

## Troubleshooting

**Common Issues**:
- **Indentation errors** - Use consistent spaces (not tabs)
- **Syntax errors** - Check for missing colons or quotes
- **Formatting issues** - Ensure consistent spacing
- **Missing files** - Verify scan paths include YAML files

**Debug Mode**:
The workflow provides detailed output showing exactly which files have issues and what needs to be fixed.
