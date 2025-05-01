// models/SensorData.js
const mongoose = require('mongoose');

const SensorDataSchema = new mongoose.Schema({
  temperatura: Number,
  umidade: Number,
  co2: Number,
  uv: Number,
  data_hora: { type: Date, default: Date.now }
});

module.exports = mongoose.model('SensorData', SensorDataSchema);
