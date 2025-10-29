# ArgoCD Installation

This guide covers installing ArgoCD in your Kubernetes cluster.

## Prerequisites

- Kubernetes cluster (v1.19 or later)
- kubectl configured to access your cluster
- RBAC permissions to create namespaces and resources

## Installation Methods

### Using kubectl

#### Create Namespace

```bash
kubectl create namespace argocd
```

#### Install ArgoCD

```bash
# Install ArgoCD
kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
```

#### Verify Installation

```bash
# Check if ArgoCD is running
kubectl get pods -n argocd

# Expected output:
# NAME                                READY   STATUS    RESTARTS   AGE
# argocd-application-controller-0     1/1     Running   0          2m
# argocd-dex-server-xxxxx             1/1     Running   0          2m
# argocd-redis-xxxxx                  1/1     Running   0          2m
# argocd-repo-server-xxxxx            1/1     Running   0          2m
# argocd-server-xxxxx                 1/1     Running   0          2m
```

### Using Helm

#### Add ArgoCD Helm Repository

```bash
helm repo add argo https://argoproj.github.io/argo-helm
helm repo update
```

#### Install ArgoCD

```bash
# Install ArgoCD
helm install argocd argo/argo-cd \
  --namespace argocd \
  --create-namespace \
  --set server.service.type=LoadBalancer
```

### Using Kustomize

#### Create kustomization.yaml

```yaml
apiVersion: kustomize.config.k8s.io/v1beta1
kind: Kustomization

namespace: argocd

resources:
  - https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

patchesStrategicMerge:
  - argocd-server-patch.yaml
```

## Access ArgoCD

### Port Forward (for testing)

```bash
# Port forward to access ArgoCD server
kubectl port-forward svc/argocd-server -n argocd 8080:443

# Access ArgoCD at https://localhost:8080
```

### LoadBalancer Service

```yaml
apiVersion: v1
kind: Service
metadata:
  name: argocd-server-lb
  namespace: argocd
spec:
  type: LoadBalancer
  ports:
  - port: 443
    targetPort: 8080
    protocol: TCP
  selector:
    app.kubernetes.io/name: argocd-server
```

### Ingress Configuration

```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: argocd-server-ingress
  namespace: argocd
  annotations:
    kubernetes.io/ingress.class: nginx
    nginx.ingress.kubernetes.io/ssl-redirect: "true"
    nginx.ingress.kubernetes.io/backend-protocol: "GRPC"
spec:
  tls:
  - hosts:
    - argocd.example.com
    secretName: argocd-server-tls
  rules:
  - host: argocd.example.com
    http:
      paths:
      - path: /
        pathType: Prefix
        backend:
          service:
            name: argocd-server
            port:
              number: 80
```

## Initial Setup

### 1. Get Admin Password

```bash
# Get initial admin password
kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data.password}" | base64 -d

# Or using ArgoCD CLI
argocd admin initial-password -n argocd
```

### 2. Login via CLI

```bash
# Install ArgoCD CLI
curl -sSL -o argocd-linux-amd64 https://github.com/argoproj/argo-cd/releases/latest/download/argocd-linux-amd64
sudo install -m 555 argocd-linux-amd64 /usr/local/bin/argocd
rm argocd-linux-amd64

# Login to ArgoCD
argocd login localhost:8080 --username admin --password <password>
```

### 3. Change Admin Password

```bash
# Change admin password
argocd account update-password --account admin
```

## Configuration

### Repository Access

#### Add Git Repository

```bash
# Add repository via CLI
argocd repo add https://github.com/example/repo.git

# Or via Web UI: Settings > Repositories > Connect Repo
```

#### SSH Key Configuration

```bash
# Create SSH key
ssh-keygen -t ed25519 -C "argocd@example.com"

# Add public key to Git repository
cat ~/.ssh/id_ed25519.pub

# Add repository with SSH
argocd repo add git@github.com:example/repo.git --ssh-private-key-path ~/.ssh/id_ed25519
```

### RBAC Configuration

#### Create RBAC ConfigMap

```yaml
apiVersion: v1
kind: ConfigMap
metadata:
  name: argocd-rbac-cm
  namespace: argocd
data:
  policy.default: role:readonly
  policy.csv: |
    p, role:admin, applications, *, */*, allow
    p, role:admin, clusters, *, *, allow
    p, role:admin, repositories, *, *, allow
    g, argocd-admins, role:admin
```

## Verification

### Check ArgoCD Status

```bash
# Check ArgoCD version
argocd version

# Check cluster connectivity
argocd cluster list

# Check repository connectivity
argocd repo list
```

### Test Application Deployment

```yaml
apiVersion: argoproj.io/v1alpha1
kind: Application
metadata:
  name: guestbook
  namespace: argocd
spec:
  project: default
  source:
    repoURL: https://github.com/argoproj/argocd-example-apps
    targetRevision: HEAD
    path: guestbook
  destination:
    server: https://kubernetes.default.svc
    namespace: default
  syncPolicy:
    automated:
      prune: true
      selfHeal: true
    syncOptions:
    - CreateNamespace=true
```

## Troubleshooting

### Common Issues

1. **ArgoCD server not accessible**
   - Check service configuration
   - Verify port forwarding
   - Check ingress configuration

2. **Repository connection failed**
   - Verify repository URL
   - Check authentication credentials
   - Verify network connectivity

3. **Application sync failed**
   - Check application manifest validity
   - Verify target cluster connectivity
   - Check RBAC permissions

### Debug Commands

```bash
# Check ArgoCD logs
kubectl logs -n argocd -l app.kubernetes.io/name=argocd-server

# Check application controller logs
kubectl logs -n argocd -l app.kubernetes.io/name=argocd-application-controller

# Check repository server logs
kubectl logs -n argocd -l app.kubernetes.io/name=argocd-repo-server
```

## Uninstallation

### Remove ArgoCD

```bash
# Delete ArgoCD namespace (removes all resources)
kubectl delete namespace argocd

# Or delete specific resources
kubectl delete -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
```

### Clean Up

```bash
# Remove ArgoCD CLI
sudo rm /usr/local/bin/argocd

# Remove Helm installation
helm uninstall argocd -n argocd
```
