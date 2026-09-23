# Docker Registry Installation

Step-by-step installation guide for deploying a Docker registry in your Kubernetes homelab cluster.

## Prerequisites

- Kubernetes cluster running (v1.24+)
- MetalLB load balancer installed and configured
- Local-path storage provisioner installed
- `kubectl` configured to access your cluster
- ArgoCD installed (optional, for GitOps deployment)

## Installation Methods

### Method 1: Manual Installation with kubectl

#### Step 1: Clone the Repository

```bash
git clone https://github.com/koriwayne/homelab.local.git
cd homelab.local
```

#### Step 2: Navigate to Registry Directory

```bash
cd applications/docker-registry
```

#### Step 3: Review Configuration

Check the kustomization.yaml to see what resources will be deployed:

```bash
cat kustomization.yaml
```

Expected resources:
- namespace.yaml
- pvc.yaml (PersistentVolumeClaim)
- configmap.yaml (Registry configuration)
- deployment.yaml (Registry pod)
- service.yaml (LoadBalancer service)

#### Step 4: Deploy Registry

```bash
kubectl apply -k .
```

#### Step 5: Verify Deployment

```bash
# Wait for pod to be ready
kubectl wait --for=condition=ready pod -l app=docker-registry \
  -n docker-registry --timeout=300s

# Check pod status
kubectl get pods -n docker-registry

# Check service and external IP
kubectl get svc -n docker-registry

# View registry logs
kubectl logs -f deployment/docker-registry -n docker-registry
```

#### Step 6: Get Registry IP

```bash
export REGISTRY_IP=$(kubectl get svc docker-registry -n docker-registry \
  -o jsonpath='{.status.loadBalancer.ingress[0].ip}')
echo "Registry accessible at: http://$REGISTRY_IP:5000"
```

Expected output:
```
NAME              TYPE           CLUSTER-IP      EXTERNAL-IP      PORT(S)          AGE
docker-registry   LoadBalancer   10.96.123.45    192.168.1.248    5000:30000/TCP   2m
```

### Method 2: GitOps Deployment with ArgoCD

#### Step 1: Push Configuration to Git

```bash
git add applications/docker-registry/
git commit -m "Add Docker registry configuration"
git push origin main
```

#### Step 2: Create ArgoCD Application

The ArgoCD application manifest is already configured in `cicd/argocd/applications/docker-registry-app.yaml`.

Verify the application:

```bash
kubectl apply -f cicd/argocd/applications/docker-registry-app.yaml
```

#### Step 3: Sync via ArgoCD UI

1. Open ArgoCD: `http://192.168.1.***`
2. Login with credentials
3. Find the `docker-registry` application
4. Click "Sync" to deploy

#### Step 4: Verify via ArgoCD

```bash
# Check application status
argocd app get docker-registry

# Or view in cluster
kubectl get application docker-registry -n argocd
```

## Post-Installation Configuration

### Configure Docker to Use Insecure Registry

#### On Linux

```bash
# Edit Docker daemon configuration
sudo nano /etc/docker/daemon.json
```

Add your registry IP:

```json
{
  "insecure-registries": ["192.168.1.***:5000"]
}
```

Restart Docker:

```bash
sudo systemctl restart docker
```

Verify configuration:

```bash
docker info | grep -A 5 "Insecure Registries"
```

#### On macOS (Docker Desktop)

1. Open Docker Desktop
2. Go to Settings → Docker Engine
3. Add to JSON configuration:

```json
{
  "insecure-registries": ["192.168.1.***:5000"]
}
```

4. Click "Apply & Restart"

### Test Registry Connectivity

```bash
# Test with curl
curl http://$REGISTRY_IP:5000/v2/

# Expected response:
# {}

# List repositories (should be empty initially)
curl http://$REGISTRY_IP:5000/v2/_catalog

# Expected response:
# {"repositories":[]}
```

### Push a Test Image

```bash
# Pull a small test image
docker pull alpine:latest

# Tag for registry
docker tag alpine:latest $REGISTRY_IP:5000/test-image:latest

# Push to registry
docker push $REGISTRY_IP:5000/test-image:latest

# Verify image is in registry
curl http://$REGISTRY_IP:5000/v2/_catalog
curl http://$REGISTRY_IP:5000/v2/test-image/tags/list
```

## Verification Checklist

- [ ] Pod is running: `kubectl get pods -n docker-registry`
- [ ] Service has external IP: `kubectl get svc -n docker-registry`
- [ ] PVC is bound: `kubectl get pvc -n docker-registry`
- [ ] Registry responds to API: `curl http://$REGISTRY_IP:5000/v2/`
- [ ] Docker can push images: `docker push $REGISTRY_IP:5000/test-image`
- [ ] Images are persisted: Restart pod and verify images remain

## Troubleshooting Installation

### Pod Stuck in Pending

```bash
# Check pod events
kubectl describe pod -n docker-registry -l app=docker-registry

# Common issues:
# - PVC not bound: Check storage class
# - Node not schedulable: Check node resources
# - Image pull errors: Check network connectivity
```

### PVC Not Binding

```bash
# Check PVC status
kubectl get pvc -n docker-registry -o yaml

# Verify storage class exists
kubectl get storageclass local-path

# Check local-path provisioner
kubectl get pods -n local-path-storage
```

### No External IP Assigned

```bash
# Check MetalLB status
kubectl get pods -n metallb-system

# Check IP pool
kubectl get ipaddresspool -n metallb-system

# Verify IP pool range
kubectl get ipaddresspool -n metallb-system -o yaml
```

### Registry Not Responding

```bash
# Check pod logs
kubectl logs -n docker-registry deployment/docker-registry

# Check configmap
kubectl get configmap -n docker-registry registry-config -o yaml

# Verify registry configuration
kubectl exec -n docker-registry deployment/docker-registry -- \
  cat /etc/docker/registry/config.yml
```

## Next Steps

After successful installation:

1. [Configure registry access](../index.md#usage-examples)
2. [Build and push custom images](../index.md#integration-with-cicd)
3. [Update CI/CD pipelines to use registry](../index.md#integration-with-cicd)
4. [Set up automated backups](../index.md#maintenance)

## Rollback

If you need to remove the registry:

```bash
# Remove deployment
kubectl delete -k applications/docker-registry/

# Or delete namespace (includes everything)
kubectl delete namespace docker-registry

# ⚠️ Warning: This will delete all registry data!
```

For more information, see the [main documentation](../index.md).

