class MemoryStats {
    constructor(total, used, free, usage) {
        this.total = total;
        this.used = used;
        this.free = free;
        this.usage = usage;
    }
}

module.exports = MemoryStats;
