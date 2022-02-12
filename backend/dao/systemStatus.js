const { systemStatus } = require('../models')

let systemStatusDao = {
  findAll: findAll,
  create: create,
  findById: findById,
  deleteById: deleteById,
  updateSystemStatus: updateSystemStatus
}

function findAll() {
  return systemStatus.findAll()
}

function findById(id) {
  return systemStatus.findByPk(id)
}

function deleteById(id) {
  return systemStatus.destroy({ where: { id: id } })
}

function create(newIrrigationMetrics) {
  return systemStatus.create(newIrrigationMetrics)
}

function updateSystemStatus(newSystemStatus, id) {
  let updatedSystemStatus = {
      status: newSystemStatus.status
  }
  return systemStatus.update(updatedSystemStatus, { where: { id: id } })
}
module.exports = systemStatusDao