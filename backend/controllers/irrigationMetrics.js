const irrigationMetricsDao = require('../dao/irrigationMetrics')

let irrigationMetricsController = {
    addIrrigationMetrics: addIrrigationMetrics,
    findIrrigationMetrics: findIrrigationMetrics,
    findIrrigationMetricsById: findIrrigationMetricsById,
    updateIrrigationMetrics: updateIrrigationMetrics,
    deleteById: deleteById
}

function addIrrigationMetrics(req, res) {
    let irrigationMetrics = req.body
    irrigationMetricsDao.create(irrigationMetrics)
        .then((data) => {
            res.send(data)
        })
        .catch((error) => {
            console.log(error)
        })
}

function findIrrigationMetricsById(req, res) {
    irrigationMetricsDao.findById(req.params.id)
        .then((data) => {
            res.send(data)
        })
        .catch((error) => {
            console.log(error)
        })
}

function deleteById(req, res) {
    irrigationMetricsDao.deleteById(req.params.id)
        .then((data) => {
            res.status(200).json({
                message: "Irrigation metrics deleted successfully",
                irrigationMetrics: data
            })
        })
        .catch((error) => {
            console.log(error)
        })
}

function updateIrrigationMetrics(req, res) {
    irrigationMetricsDao.updateIrrigationMetrics(req.body, req.params.id)
        .then((data) => {
            res.status(200).json({
                message: "Irrigation metrics updated successfully",
                irrigationMetrics: data
            })
        })
        .catch((error) => {
            console.log(error)
        })
}

function findIrrigationMetrics(req, res) {
    irrigationMetricsDao.findAll()
        .then((data) => {
            res.send(data)
        })
        .catch((error) => {
            console.log(error)
        })
}

module.exports = irrigationMetricsController