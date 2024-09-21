const os = require('os');
const { execSync } = require('child_process');

class SystemMonitorService {
    constructor() {
        this.prevCPUTimes = os.cpus().map(cpu => cpu.times);
    }

    getCPUStats() {
        const cpus = os.cpus();
        const cpuStats = [];

        cpus.forEach((cpu, index) => {
            const totalTime = Object.values(cpu.times).reduce((acc, time) => acc + time, 0);
            const idleTime = cpu.times.idle;

            const prevTotalTime = Object.values(this.prevCPUTimes[index]).reduce((acc, time) => acc + time, 0);
            const prevIdleTime = this.prevCPUTimes[index].idle;

            const deltaTotal = totalTime - prevTotalTime;
            const deltaIdle = idleTime - prevIdleTime;

            const cpuUsage = (1 - deltaIdle / deltaTotal) * 100;
            cpuStats.push({
                model: cpu.model,
                speed: cpu.speed,
                usage: Math.round(cpuUsage),
            });
        });

        this.prevCPUTimes = cpus.map(cpu => cpu.times);

        return cpuStats;
    }

    getMemoryStats() {
        const total = os.totalmem();
        const free = os.freemem();
        const used = total - free;

        return {
            total,
            used,
            free,
            usage: Math.round((used / total) * 100),
        };
    }

    getDiskStats() {
        try {
            if (os.platform() === 'win32') {
                const output = execSync('wmic logicaldisk get size,freespace,caption', { encoding: 'utf8' });
                const lines = output.trim().split('\n');
                const disks = lines.slice(1).map(line => {
                    const [caption, freespace, size] = line.trim().split(/\s+/);
                    const used = size - freespace;
                    return {
                        mount: caption,
                        total: parseInt(size),
                        used: parseInt(used),
                        available: parseInt(freespace),
                        usage: Math.round((used / size) * 100),
                    };
                });
                return disks;
            } else {
                const output = execSync('df -h', { encoding: 'utf8' });
                const lines = output.trim().split('\n');
                const disks = lines.slice(1).map(line => {
                    const parts = line.trim().split(/\s+/);
                    const used = parseInt(parts[2].replace(/[^\d]/g, ''));
                    const total = parseInt(parts[1].replace(/[^\d]/g, ''));
                    return {
                        filesystem: parts[0],
                        total,
                        used,
                        available: parseInt(parts[3].replace(/[^\d]/g, '')),
                        usage: Math.round((used / total) * 100),
                        mount: parts[5],
                    };
                });
                return disks;
            }
        } catch (error) {
            console.error('Error getting disk stats:', error);
            return [];
        }
    }

    getNetworkStats() {
        const interfaces = os.networkInterfaces();
        const networkData = Object.keys(interfaces).map(iface => ({
            interface: iface,
            addresses: interfaces[iface].map(ifaceDetails => ({
                address: ifaceDetails.address,
                netmask: ifaceDetails.netmask,
                mac: ifaceDetails.mac,
            })),
        }));

        return networkData;
    }

    getAllStats() {
        return {
            cpu: this.getCPUStats(),
            memory: this.getMemoryStats(),
            disk: this.getDiskStats(),
            network: this.getNetworkStats(),
        };
    }
}

module.exports = SystemMonitorService;
