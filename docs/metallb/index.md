# MetalLB Documentation

MetalLB is a load-balancer implementation for bare metal Kubernetes clusters. This documentation covers installation, configuration, and management of MetalLB in your Kubernetes environment.

## Table of Contents

- [Installation](installation.md)
- [Configuration](configuration.md)
- [Layer 2 Mode](layer2-mode.md)
- [BGP Mode](bgp-mode.md)
- [IP Address Pools](ip-pools.md)
- [Service Configuration](service-config.md)
- [Troubleshooting](troubleshooting.md)
- [Security Considerations](security.md)

## Overview

MetalLB provides a network load-balancer implementation for Kubernetes clusters that don't run on a cloud provider, and thus cannot simply use LoadBalancer services.

### Key Features

- **Bare Metal Support**: Works on bare metal Kubernetes clusters
- **Multiple Modes**: Layer 2 and BGP support
- **IP Address Management**: Automatic IP assignment from pools
- **Service Integration**: Works with standard Kubernetes services
- **High Availability**: Support for multiple load balancer nodes

## Architecture

MetalLB consists of two components:

- **Speaker**: Runs on each node and handles the actual load balancing
- ** Controller**: Runs as a single instance and manages IP address assignments

## Quick Start

1. [Install MetalLB](installation.md)
2. [Configure IP address pools](ip-pools.md)
3. [Create a LoadBalancer service](service-config.md)

## Prerequisites

- Kubernetes cluster (v1.13.0+)
- Cluster with no existing load balancer provider
- For BGP mode: BGP-capable router
- For Layer 2 mode: Network connectivity between nodes
