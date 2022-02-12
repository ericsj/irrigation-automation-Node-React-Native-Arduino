const { irrigationMetrics } = require('../models')

let irrigationMetricsDao = {
  findAll: findAll,
  create: create,
  findById: findById,
  deleteById: deleteById,
  updateIrrigationMetrics: updateIrrigationMetrics
}

function findAll() {
  return irrigationMetrics.findAll()
}

function findById(id) {
  return irrigationMetrics.findByPk(id)
}

function deleteById(id) {
  return irrigationMetrics.destroy({ where: { id: id } })
}

function create(newIrrigationMetrics) {
  return irrigationMetrics.create(newIrrigationMetrics)
}

function updateIrrigationMetrics(newIrrigationMetrics, id) {
  let updatedIrrigationMetrics = {
      duration: newIrrigationMetrics.duration,
      initialMoisture: newIrrigationMetrics.initialMoisture,
      finalMoisture: newIrrigationMetrics.finalMoisture
  }
  return irrigationMetrics.update(updatedIrrigationMetrics, { where: { id: id } })
}
module.exports = irrigationMetricsDao