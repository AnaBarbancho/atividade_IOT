// src/components/Dashboard.js
import React, { useEffect, useState } from 'react';
import axios from 'axios';
import { Line } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
} from 'chart.js';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

const Dashboard = () => {
  const [dados, setDados] = useState([]);

  useEffect(() => {
    const fetchDados = async () => {
      try {
        const response = await axios.get('http://localhost:3000/api/dados'); // ajuste se necessário
        setDados(response.data);
      } catch (error) {
        console.error('Erro ao buscar dados:', error);
      }
    };

    fetchDados();
  }, []);

  const labels = dados.map(d => new Date(d.data_hora).toLocaleTimeString());

  const data = {
    labels,
    datasets: [
      {
        label: 'Temperatura (°C)',
        data: dados.map(d => d.temperatura),
        borderColor: 'red',
        backgroundColor: 'rgba(255,0,0,0.1)',
        tension: 0.4
      },
      {
        label: 'Umidade (%)',
        data: dados.map(d => d.umidade),
        borderColor: 'blue',
        backgroundColor: 'rgba(0,0,255,0.1)',
        tension: 0.4
      },
      {
        label: 'CO₂ (ppm)',
        data: dados.map(d => d.co2),
        borderColor: 'green',
        backgroundColor: 'rgba(0,255,0,0.1)',
        tension: 0.4
      },
      {
        label: 'Radiação UV',
        data: dados.map(d => d.uv),
        borderColor: 'purple',
        backgroundColor: 'rgba(128,0,128,0.1)',
        tension: 0.4
      }
    ]
  };

  const options = {
    responsive: true,
    plugins: {
      legend: { position: 'top' },
      title: { display: true, text: 'Dados dos Sensores' }
    }
  };

  return (
    <div>
      <h2>Dashboard de Sensores</h2>
      <Line data={data} options={options} />
    </div>
  );
};

export default Dashboard;
