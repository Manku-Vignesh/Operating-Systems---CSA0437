const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const si = require('systeminformation');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

app.use(express.static(__dirname + '/public'));

const getSystemStats = async () => {
    const cpuUsage = await si.currentLoad();
    const memoryUsage = await si.mem();
    const diskUsage = await si.fsSize();
    const networkStats = await si.networkStats();
    const gpuUsage = await si.graphics();

    return {
        cpuUsage: cpuUsage.currentLoad,
        memoryUsage: (memoryUsage.active / memoryUsage.total) * 100,
        diskUsage: diskUsage[0].use,
        networkStats: {
            wifi: {
                down: networkStats[0].rx_sec,
                up: networkStats[0].tx_sec
            },
            ethernet: {
                down: networkStats[1] ? networkStats[1].rx_sec : 0,
                up: networkStats[1] ? networkStats[1].tx_sec : 0
            }
        },
        gpuUsage: gpuUsage.controllers[0].memoryUsed / gpuUsage.controllers[0].memoryTotal * 100
    };
};

io.on('connection', (socket) => {
    console.log('New client connected');

    setInterval(async () => {
        const systemStats = await getSystemStats();
        socket.emit('system-stats', systemStats);
    }, 1000);

    socket.on('disconnect', () => {
        console.log('Client disconnected');
    });
});

server.listen(3000, () => {
    console.log('Listening on port 3000');
});
