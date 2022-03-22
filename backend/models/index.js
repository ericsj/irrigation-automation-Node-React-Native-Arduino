const Sequelize = require('sequelize')
const sequelize = require('../config/sequelize')

const IrrigationMetrics = require('./irrigationMetrics')
const irrigationMetrics = IrrigationMetrics(sequelize, Sequelize.DataTypes)

const db = {
  irrigationMetrics,
  sequelize
}

module.exports = db
