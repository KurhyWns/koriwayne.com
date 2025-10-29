# Kori Hanes
## DevSecOps & GitOps Portfolio

Welcome to my comprehensive DevSecOps and GitOps portfolio! This site showcases my expertise in modern software development practices, infrastructure automation, and security-first development methodologies.

## Website Status
✅ **Successfully hosted on GitHub Pages with custom domain!**

## About This Portfolio

This portfolio demonstrates my expertise in **DevSecOps** and **GitOps** methodologies, showcasing projects that integrate security throughout the entire software development lifecycle:

- **Infrastructure as Code (IaC)** implementations with Docker, Kubernetes, and Terraform
- **Continuous Integration/Continuous Deployment (CI/CD)** pipelines with automated security scanning
- **Security-first development** practices with comprehensive quality gates
- **Automated testing and validation** including secrets detection and code quality checks
- **GitOps workflows** for reliable deployments with branch protection
- **Container orchestration** and microservices architecture with security validation
- **Compliance and governance** automation with infrastructure security scanning

## Project Portfolio

### 🏠 **Home Lab Infrastructure**
- **Repository**: [homeLab](https://github.com/KurhyWns/homeLab)
- **Focus**: Self-hosted infrastructure with Docker, Kubernetes, and automation
- **Technologies**: Docker, Kubernetes, Terraform, Ansible, Prometheus, Grafana

### 🔄 **Shared Pipeline Strategy**
- **Repository**: [shared-pipeline](https://github.com/KurhyWns/shared-pipeline)
- **Focus**: Reusable CI/CD workflows and security scanning
- **Technologies**: GitHub Actions, TruffleHog, GitLeaks, Hadolint, kubeval

### 📚 **Documentation & Learning**
- **Gitea**: Self-hosted Git server documentation
- **MetalLB**: Load balancer for bare metal Kubernetes
- **ArgoCD**: GitOps continuous delivery tool
- **Branching Strategy**: GitFlow with security enforcement

## Security & Quality Pipeline

This portfolio implements comprehensive security and quality checks across all projects:

### 🔒 **Secrets Detection** ✅ **IMPLEMENTED**
- **TruffleHog OSS**: ✅ **ACTIVE** - Scans entire repository for hardcoded secrets and credentials
- **GitLeaks**: Planned for future implementation
- **detect-secrets**: Planned for future implementation

**Current Implementation**:
- Runs on every push to `main` branch
- Runs on all pull requests to `main`
- Uses shared-pipeline workflow for consistency
- Scans entire repository (not just changed files)
- Only reports verified secrets (reduces false positives)

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

### 🐳 **Infrastructure Security**
- **Hadolint**: Dockerfile best practices and security
- **kubeval**: Kubernetes manifest validation
- **kube-score**: Kubernetes security and best practices
- **Helm**: Helm chart linting
- **Terraform**: Infrastructure code linting and formatting

## Repository Information
- **Portfolio Repository**: [koriwayne.com](https://github.com/KurhyWns/koriwayne.com)
- **Custom Domain**: [koriwayne.com](https://koriwayne.com)
- **Home Lab**: [homeLab](https://github.com/KurhyWns/homeLab)
- **Shared Pipelines**: [shared-pipeline](https://github.com/KurhyWns/shared-pipeline)

---

*Navigate through the projects and documentation using the menu above to explore each component in detail.*
