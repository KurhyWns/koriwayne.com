# Git Branching Strategy From Develop To Main

This document outlines the branching strategy and workflow for the koriwayne.com project, ensuring code quality, review processes, and safe deployments.

## Overview

Our branching strategy follows GitFlow principles with additional security measures to prevent direct pushes to main and ensure all changes go through proper review processes.

## Branch Structure

```
main (production)
├── develop (integration)
│   ├── feature/feature-name
│   ├── feature/another-feature
│   └── hotfix/critical-fix
└── release/v1.0.0
```

### Visual Diagram

![Branching Strategy](images/branching.png){ width="900" }


## Branch Types

### 1. **Main Branch** (`main`)
- **Purpose**: Production-ready code
- **Protection**: Full protection with required reviews
- **Deployment**: Automatically deploys to production via GitHub Actions
- **Access**: No direct pushes allowed

### 2. **Develop Branch** (`develop`)
- **Purpose**: Integration branch for features
- **Protection**: Requires pull request reviews
- **Deployment**: Staging environment (if configured)
- **Access**: No direct pushes allowed

### 3. **Feature Branches** (`feature/*`)
- **Purpose**: New features and enhancements
- **Naming**: `feature/descriptive-name` (e.g., `feature/mkdocs-conversion`)
- **Lifecycle**: Created from `develop`, merged back to `develop`
- **Access**: Direct pushes allowed for feature development

### 4. **Release Branches** (`release/*`)
- **Purpose**: Prepare releases for production
- **Naming**: `release/v1.0.0` (semantic versioning)
- **Lifecycle**: Created from `develop`, merged to both `develop` and `main`
- **Access**: Direct pushes allowed for release preparation

### 5. **Hotfix Branches** (`hotfix/*`)
- **Purpose**: Critical fixes for production
- **Naming**: `hotfix/descriptive-name` (e.g., `hotfix/security-patch`)
- **Lifecycle**: Created from `main`, merged to both `main` and `develop`
- **Access**: Direct pushes allowed for urgent fixes

## Workflow Process

### Feature Development

1. **Start from develop**
   ```bash
   git checkout develop
   git pull origin develop
   ```

2. **Create feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Develop and commit**
   ```bash
   git add .
   git commit -m "Add your feature description"
   git push -u origin feature/your-feature-name
   ```

4. **Create Pull Request**
   - Source: `feature/your-feature-name`
   - Target: `develop`
   - Add reviewers and description

5. **After review and approval**
   - Merge PR to `develop`
   - Delete feature branch

### Release Process

1. **Create release branch**
   ```bash
   git checkout develop
   git pull origin develop
   git checkout -b release/v1.0.0
   ```

2. **Prepare release**
   - Update version numbers
   - Update changelog
   - Test thoroughly

3. **Create Pull Request**
   - Source: `release/v1.0.0`
   - Target: `main`
   - Add reviewers and description

4. **After review and approval**
   - Merge PR to `main`
   - Tag the release: `git tag v1.0.0`
   - Merge back to `develop`
   - Delete release branch

### Hotfix Process

1. **Create hotfix branch**
   ```bash
   git checkout main
   git pull origin main
   git checkout -b hotfix/critical-fix
   ```

2. **Implement fix**
   ```bash
   git add .
   git commit -m "Fix critical issue"
   git push -u origin hotfix/critical-fix
   ```

3. **Create Pull Request**
   - Source: `hotfix/critical-fix`
   - Target: `main`
   - Add reviewers and description

4. **After review and approval**
   - Merge PR to `main`
   - Merge back to `develop`
   - Delete hotfix branch

## Branch Protection Rules

### Main Branch Protection

- ✅ **Require a pull request before merging**
- ✅ **Require approvals** (1)
- ✅ **Dismiss stale PR approvals when new commits are pushed**
- ✅ **Require review from code owners**
- ✅ **Require status checks to pass before merging**
- ✅ **Require branches to be up to date before merging**
- ✅ **Require conversation resolution before merging**
- ✅ **Require signed commits**
- ✅ **Require linear history**
- ✅ **Include administrators**
- ✅ **Restrict pushes that create files larger than 100 MB**

### Develop Branch Protection

- ✅ **Require a pull request before merging**
- ✅ **Require approvals** (1)
- ✅ **Include administrators**
- ✅ **Restrict pushes that create files larger than 100 MB**

## Commit Message Convention

### Format
```
type(scope): description

[optional body]

[optional footer]
```

### Types
- **feat**: New feature
- **fix**: Bug fix
- **docs**: Documentation changes
- **style**: Code style changes (formatting, etc.)
- **refactor**: Code refactoring
- **test**: Adding or updating tests
- **chore**: Maintenance tasks

### Examples
```
feat(mkdocs): add DevSecOps documentation sections
fix(ci): resolve GitHub Actions deployment issue
docs(branching): update workflow process documentation
```

## Code Review Guidelines

### For Reviewers
- Review code for functionality, security, and maintainability
- Check for proper testing and documentation
- Ensure commit messages follow convention
- Verify branch naming follows strategy

### For Authors
- Keep PRs focused and reasonably sized
- Provide clear descriptions and context
- Respond to feedback promptly
- Ensure all checks pass before requesting review

## Emergency Procedures

### Bypass Protection (Emergency Only)
If emergency access to main is required:

1. **Contact repository administrators**
2. **Document the emergency and reason**
3. **Use GitHub's "Restrict pushes" bypass** (temporary)
4. **Follow up with proper hotfix process**

### Rollback Process
```bash
# Identify the commit to rollback to
git log --oneline

# Create rollback branch
git checkout -b hotfix/rollback-to-commit-hash

# Revert changes
git revert <commit-hash>

# Create PR for rollback
# Source: hotfix/rollback-to-commit-hash
# Target: main
```

## Best Practices

1. **Keep branches up to date** with their base branch
2. **Use descriptive branch names** that explain the purpose
3. **Write clear commit messages** following the convention
4. **Test thoroughly** before creating pull requests
5. **Review your own code** before requesting review
6. **Keep pull requests focused** and reasonably sized
7. **Delete feature branches** after merging
8. **Use draft pull requests** for work in progress

## Tools and Automation

### GitHub Actions
- **Automated testing** on pull requests
- **Automated deployment** on main branch merge
- **Security scanning** for vulnerabilities
- **Code quality checks** with linting

### Required Status Checks
- **Build verification**
- **Test suite execution**
- **Security scan results**
- **Code coverage reports**

## Troubleshooting

### Common Issues

1. **Branch protection prevents push**
   - Solution: Create a pull request instead of direct push

2. **Merge conflicts**
   - Solution: Rebase feature branch on latest develop/main

3. **Failed status checks**
   - Solution: Fix issues and push new commits

4. **Stale branch**
   - Solution: Update branch with latest changes from base branch

### Getting Help
- Check GitHub's branch protection documentation
- Review this branching strategy guide
- Contact repository administrators
- Check project's contributing guidelines

## Changing the Default Branch in GitHub (to develop)

Follow these steps to set `develop` as the default branch for this repository:

1. Create and push `develop` if it doesn't exist:
   ```bash
   git checkout -b develop
   git push -u origin develop
   ```
2. In GitHub, go to: Settings → Branches → Default branch → Change default branch.
3. Select `develop` and confirm.
4. Verify CI triggers include `main` and `develop` in `.github/workflows/ci.yml`:
   ```yaml
   "on":
     push:
       branches: [main, develop]
     pull_request:
       branches: [main, develop]
   ```
5. Protect `main` and `develop` per the rules above (Settings → Branches → Add rule).
