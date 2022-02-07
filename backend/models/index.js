const Sequelize = require('sequelize')
const sequelize = require('../config/sequelize')

const IrrigationMetrics = require('./irrigationMetrics')
const SystemStatus = require('./systemStatus')
const irrigationMetrics = IrrigationMetrics(sequelize, Sequelize.DataTypes)
const systemStatus = SystemStatus(sequelize, Sequelize.DataTypes)

const db = {
  irrigationMetrics,
  systemStatus,
  sequelize
}

module.exports = db
