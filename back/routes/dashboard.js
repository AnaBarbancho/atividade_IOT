const express = require('express');
const router = express.Router();
const SensorData = require('../models/SensorData');  // Importar o modelo de dados do sensor

// Rota para pegar os dados do sensor
router.get('/dados', async (req, res) => {
  try {
    const dados = await SensorData.find();  // Buscar todos os dados dos sensores no banco

    // Organizar os dados em um formato mais acessível, se necessário
    res.json(dados);
  } catch (err) {
    res.status(500).send('Erro ao buscar dados do sensor');
  }
});

module.exports = router;
