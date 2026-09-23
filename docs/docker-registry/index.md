# Docker Registry Documentation

A local Docker registry for storing custom container images in your Kubernetes homelab cluster.

## Overview

This deployment provides a simple, persistent Docker registry running on Kubernetes. It uses the official `registry:2` image and is configured with persistent storage, image deletion enabled, and MetalLB LoadBalancer integration.

### Key Features

- **Persistent Storage**: 50Gi PVC using local-path storage class
- **Image Deletion**: Enabled for registry cleanup
- **Health Checks**: Configured for pod health monitoring
- **LoadBalancer**: MetalLB assigns external IP automatically
- **Insecure Registry**: Configured for local development use

## Architecture

The Docker registry deployment consists of:

```
┌─────────────────────────────────────────────┐
│          Docker Registry Deployment         │
├─────────────────────────────────────────────┤
│  Namespace: docker-registry                 │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Deployment                           │  │
│  │  - Image: registry:2                  │  │
│  │  - Replicas: 1                        │  │
│  │  - Port: 5000                         │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Service (LoadBalancer)               │  │
│  │  - Type: LoadBalancer                 │  │
│  │  - External IP: MetalLB assigned      │  │
│  └──────────────────────────────────────┘  │
│                                             │
│  ┌──────────────────────────────────────┐  │
│  │  Persistent Volume                   │  │
│  │  - Size: 50Gi                        │  │
│  │  - Storage Class: local-path         │  │
│  └──────────────────────────────────────┘  │
└─────────────────────────────────────────────┘
```

## Quick Start

### Deploy the Registry

```bash
cd /docker-registry
kubectl apply -k .
```

### Verify Deployment

```bash
# Check pod status
kubectl get pods -n docker-registry

# Check service and external IP
kubectl get svc -n docker-registry

# Get the registry IP
export REGISTRY_IP=$(kubectl get svc docker-registry -n docker-registry \
  -o jsonpath='{.status.loadBalancer.ingress[0].ip}')
echo "Registry IP: $REGISTRY_IP"
```

### Configure Docker

Configure Docker on your local machine to use the insecure registry:

```json
// /etc/docker/daemon.json
{
  "insecure-registries": ["192.168.1.***:5000"]
}
```

Restart Docker:

```bash
# Linux
sudo systemctl restart docker

# macOS
# Restart Docker Desktop from the menu
```

## Usage Examples

### Push Images

```bash
# Tag your image
docker tag custom-ci:latest $REGISTRY_IP:5000/custom-ci:latest

# Push to registry
docker push $REGISTRY_IP:5000/custom-ci:latest
```

### Pull Images

```bash
# Pull from registry
docker pull $REGISTRY_IP:5000/custom-ci:latest
```

### Use in Kubernetes Pods

Pods in the cluster can access the registry using the service DNS:

```yaml
apiVersion: v1
kind: Pod
spec:
  containers:
  - name: app
    image: docker-registry.docker-registry.svc.cluster.local:5000/custom-ci:latest
```

### Use in GitLab CI

Update `.gitlab-ci.yml` to use custom images:

```yaml
security-scan:
  stage: security
  image: docker-registry.docker-registry.svc.cluster.local:5000/custom-ci:latest
  script:
    - detect-secrets scan --baseline || true
  tags:
    - local-k8-runner
```

## Maintenance

### View Registry Contents

```bash
# List all repositories
curl $REGISTRY_IP:5000/v2/_catalog

# List tags for a repository
curl $REGISTRY_IP:5000/v2/custom-ci/tags/list
```

### Monitor Registry Health

```bash
# View registry logs
kubectl logs -f deployment/docker-registry -n docker-registry

# Check pod events
kubectl describe pod -n docker-registry -l app=docker-registry
```

### Backup Registry Data

```bash
# Create backup
kubectl exec -n docker-registry deployment/docker-registry -- \
  tar -czf - -C /var/lib/registry . | \
  gzip > registry-backup-$(date +%Y%m%d).tar.gz

# Restore from backup
tar -xzf registry-backup-*.tar.gz | \
  kubectl exec -i -n docker-registry deployment/docker-registry -- \
  tar -xzf - -C /var/lib/registry
```

## Configuration

### Storage

The registry uses a 50Gi persistent volume with the local-path storage class. To increase storage:

```bash
# Delete PVC (data will be lost)
kubectl delete pvc registry-data -n docker-registry

# Edit pvc.yaml to increase size
# Then redeploy
kubectl apply -k .
```

### Registry Settings

Registry configuration is managed via ConfigMap:

```yaml
# ConfigMap settings
- Storage: filesystem with in-memory cache
- Deletion: enabled for cleanup
- Health checks: enabled
- Headers: X-Content-Type-Options set to nosniff
```

## Security Considerations

⚠️ **Important**: This registry is configured as an **insecure registry** for local development.

**Current Configuration**:
- ❌ No TLS/HTTPS encryption
- ❌ No authentication required
- ✅ Insecure registry mode
- ✅ Local/trusted network use only

**Production Recommendations**:
- Use Harbor for feature-rich enterprise registry
- Set up TLS certificates with cert-manager
- Implement authentication with Harbor or GitLab Container Registry
- Use proper RBAC and network policies
- Enable vulnerability scanning

## Troubleshooting

### Registry Not Starting

```bash
# Check pod events
kubectl describe pod -n docker-registry -l app=docker-registry

# Check PVC status
kubectl get pvc -n docker-registry

# Verify storage class exists
kubectl get storageclass
```

### Can't Push to Registry

1. Verify Docker daemon configuration: `/etc/docker/daemon.json`
2. Restart Docker after configuration changes
3. Verify registry IP is correct: `kubectl get svc -n docker-registry`
4. Check registry logs: `kubectl logs -n docker-registry deployment/docker-registry`

### No External IP Assigned

```bash
# Check MetalLB status
kubectl get pods -n metallb-system

# Verify IP pool
kubectl get ipaddresspool -n metallb-system

# Check L2 advertisement
kubectl get l2advertisement -n metallb-system
```

## Integration with CI/CD

### Custom CI Images

Build and push custom CI images to optimize GitLab CI job execution:

```bash
# Build custom CI image
cd /custom-ci-image
docker build -t $REGISTRY_IP:5000/custom-ci:latest .

# Push to registry
docker push $REGISTRY_IP:5000/custom-ci:latest
```

### Automated Builds

Consider setting up automated image builds with:
- **Kaniko**: Build images in Kubernetes without Docker daemon
- **BuildKit**: Advanced build capabilities
- **GitHub Actions**: CI/CD workflows for image builds
- **ArgoCD**: GitOps-based image deployment

## Related Documentation

- [MetalLB Load Balancer](../metallb/index.md)
- [ArgoCD GitOps](../argocd/index.md)
- [Custom CI Image](../projects/homelab/index.md#custom-ci-image)

## Additional Resources

- [Docker Registry Documentation](https://docs.docker.com/registry/)
- [Kubernetes Persistent Volumes](https://kubernetes.io/docs/concepts/storage/persistent-volumes/)
- [MetalLB Documentation](https://metallb.universe.tf/)
- [Harbor Documentation](https://goharbor.io/docs/)

