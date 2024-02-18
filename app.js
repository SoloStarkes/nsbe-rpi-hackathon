// Sample data for spending pie chart
const spendingData = {
    labels: ['Food', 'Rent', 'Utilities', 'Transportation', 'Entertainment'],
    data: [300, 1000, 500, 200, 300]
};

// Sample data for sideways bar chart (budget)
const budgetData = {
    labels: ['Food', 'Rent', 'Utilities', 'Transportation', 'Entertainment'],
    data: [400, 1200, 600, 300, 400]
};

// Function to draw spending pie chart
function drawSpendingPieChart() {
    const ctx = document.getElementById('spendingPieChart').getContext('2d');
    new Chart(ctx, {
        type: 'pie',
        data: {
            labels: spendingData.labels,
            datasets: [{
                data: spendingData.data,
                backgroundColor: [
                    '#ff6384',
                    '#36a2eb',
                    '#ffce56',
                    '#4bc0c0',
                    '#9966ff'
                ]
            }]
        }
    });
}

// Function to draw sideways bar chart (budget)
function drawSidewaysBarChart() {
    const container = document.getElementById('sidewaysBarChart');
    budgetData.labels.forEach((label, index) => {
        const bar = document.createElement('div');
        bar.classList.add('bar');
        bar.style.width = `${budgetData.data[index]}px`;
        bar.textContent = `${label}: $${budgetData.data[index]}`;
        container.appendChild(bar);
    });
}

// Call functions to draw charts when the page loads
window.onload = function() {
    drawSpendingPieChart();
    drawSidewaysBarChart();
};
