window.onload = function() {
    const cpuWidget = new SystemStatWidget('cpuChart', '/api/stats/cpu');
    const memoryWidget = new SystemStatWidget('memoryChart', '/api/stats/memory');
    const diskWidget = new SystemStatWidget('diskChart', '/api/stats/disk', true); // Multiple datasets for disks
    const networkWidget = new SystemStatWidget('networkList', '/api/stats/network', false, true); // Non-chart for network

    cpuWidget.fetchAndRenderData();
    memoryWidget.fetchAndRenderData();
    diskWidget.fetchAndRenderData();
    networkWidget.fetchAndRenderData();

    setInterval(() => {
        cpuWidget.fetchAndRenderData();
        memoryWidget.fetchAndRenderData();
        diskWidget.fetchAndRenderData();
        networkWidget.fetchAndRenderData();
    }, 5000);  // Update every 5 seconds
};

function SystemStatWidget(widgetId, dataUrl, isMultiDataset = false, isList = false) {
    this.widgetId = widgetId;
    this.dataUrl = dataUrl;
    this.chart = null;

    this.fetchAndRenderData = async function() {
        const response = await fetch(this.dataUrl);
        const data = await response.json();
        if (isList) {
            this.renderList(data);
        } else {
            this.renderChart(data, isMultiDataset);
        }
    };

    this.renderChart = function(data, isMultiDataset) {
        if (!this.chart) {
            const datasets = isMultiDataset ? data.map((disk, index) => ({
                label: `Disk ${index + 1} - ${disk.mount}`,
                data: [disk.usage],
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                borderColor: 'rgba(75, 192, 192, 1)'
            })) : [{
                label: 'Usage (%)',
                data: data.values,
                borderColor: 'rgba(75, 192, 192, 1)',
                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                fill: true
            }];

            this.chart = new Chart(document.getElementById(this.widgetId), {
                type: 'line',
                data: {
                    labels: data.timestamps || ['Current'],
                    datasets: datasets
                },
                options: {
                    scales: {
                        x: { title: { display: true, text: 'Time' } },
                        y: { title: { display: true, text: 'Usage (%)' }, min: 0, max: 100 }
                    }
                }
            });
        } else {
            this.chart.data.datasets = isMultiDataset ? data.map((disk, index) => ({
                label: `Disk ${index + 1} - ${disk.mount}`,
                data: [disk.usage]
            })) : [{ data: data.values }];
            this.chart.update();
        }
    };

    this.renderList = function(data) {
        const listElement = document.getElementById(this.widgetId);
        listElement.innerHTML = ''; // Clear previous data
        data.forEach(interface => {
            const ifaceInfo = `
                <div>
                    <h3>${interface.interface}</h3>
                    <ul>
                        ${interface.addresses.map(addr => `<li>${addr.address} (${addr.mac}) - Netmask: ${addr.netmask}</li>`).join('')}
                    </ul>
                </div>`;
            listElement.innerHTML += ifaceInfo;
        });
    };
}
