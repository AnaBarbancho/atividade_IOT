// backend/index.js
const express = require('express');
const app = express();
const mongoose = require('mongoose');
const cors = require('cors');
const dashboardRoutes = require('./routes/dashboard');

app.use(cors());
app.use(express.json()); // Permite o envio de dados em formato JSON

// Conectar ao MongoDB
mongoose.connect('mongodb://localhost/sensores', {
  useNewUrlParser: true,
  useUnifiedTopology: true,
})
  .then(() => console.log("Conectado ao MongoDB"))
  .catch((err) => console.error("Erro de conexão:", err));

// Usar as rotas do dashboard
app.use('/api', dashboardRoutes);

const port = 3000;
app.listen(port, () => console.log(`Servidor rodando na porta ${port}`));
