# MetalLB Installation

This guide covers installing MetalLB in your Kubernetes cluster.

## Prerequisites

- Kubernetes cluster (v1.13.0 or later)
- kubectl configured to access your cluster
- No existing load balancer provider installed

## Installation Methods

### Using kubectl

#### Install MetalLB

```bash
# Apply the MetalLB manifest
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.13.12/config/manifests/metallb-native.yaml
```

#### Verify Installation

```bash
# Check if MetalLB is running
kubectl get pods -n metallb-system

# Expected output:
# NAME                          READY   STATUS    RESTARTS   AGE
# controller-7d4b5b5b5b-xxxxx   1/1     Running   0          1m
# speaker-xxxxx                 1/1     Running   0          1m
```

### Using Helm

#### Add MetalLB Helm Repository

```bash
helm repo add metallb https://metallb.github.io/metallb
helm repo update
```

#### Install MetalLB

```bash
# Install MetalLB
helm install metallb metallb/metallb

# Or with custom values
helm install metallb metallb/metallb \
  --namespace metallb-system \
  --create-namespace \
  --set speaker.frr.enabled=true
```

### Using Kustomize

#### Create kustomization.yaml

```yaml
apiVersion: kustomize.config.k8s.io/v1beta1
kind: Kustomization

resources:
  - https://raw.githubusercontent.com/metallb/metallb/v0.13.12/config/manifests/metallb-native.yaml

patchesStrategicMerge:
  - metallb-config.yaml
```

#### Apply with Kustomize

```bash
kubectl apply -k .
```

## Post-Installation Configuration

### 1. Create IP Address Pool

```yaml
apiVersion: metallb.io/v1beta1
kind: IPAddressPool
metadata:
  name: first-pool
  namespace: metallb-system
spec:
  addresses:
  - 192.168.1.240-192.168.1.250
```

### 2. Create L2Advertisement

```yaml
apiVersion: metallb.io/v1beta1
kind: L2Advertisement
metadata:
  name: example
  namespace: metallb-system
spec:
  ipAddressPools:
  - first-pool
```

### 3. Apply Configuration

```bash
kubectl apply -f metallb-config.yaml
```

## Verification

### Check MetalLB Status

```bash
# Check controller logs
kubectl logs -n metallb-system controller-xxxxx

# Check speaker logs
kubectl logs -n metallb-system speaker-xxxxx

# Check IP address pools
kubectl get ipaddresspools -n metallb-system

# Check L2 advertisements
kubectl get l2advertisements -n metallb-system
```

### Test LoadBalancer Service

```yaml
apiVersion: v1
kind: Service
metadata:
  name: test-service
spec:
  selector:
    app: test
  ports:
  - port: 80
    targetPort: 8080
  type: LoadBalancer
```

```bash
# Apply test service
kubectl apply -f test-service.yaml

# Check service status
kubectl get service test-service

# Expected output should show an EXTERNAL-IP assigned
```

## Troubleshooting

### Common Issues

1. **No IP assigned to LoadBalancer service**
   - Check if IP address pool is configured
   - Verify L2Advertisement or BGPAdvertisement is created
   - Check speaker logs for errors

2. **Speaker pods not starting**
   - Check node labels and taints
   - Verify RBAC permissions
   - Check for port conflicts

3. **Controller not responding**
   - Check controller logs
   - Verify webhook configuration
   - Check RBAC permissions

### Debug Commands

```bash
# Check MetalLB events
kubectl get events -n metallb-system

# Describe IP address pool
kubectl describe ipaddresspool first-pool -n metallb-system

# Check speaker configuration
kubectl describe node <node-name>
```

## Uninstallation

### Remove MetalLB

```bash
# Delete MetalLB resources
kubectl delete -f https://raw.githubusercontent.com/metallb/metallb/v0.13.12/config/manifests/metallb-native.yaml

# Or if using Helm
helm uninstall metallb
```

### Clean Up

```bash
# Remove any remaining MetalLB resources
kubectl delete namespace metallb-system

# Clean up any remaining IP addresses
kubectl delete ipaddresspools --all-namespaces --all
kubectl delete l2advertisements --all-namespaces --all
kubectl delete bgpadvertisements --all-namespaces --all
```
