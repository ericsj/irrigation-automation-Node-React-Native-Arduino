const systemStatusDao = require('../dao/systemStatus')

let systemStatusController = {
    addSystemStatus: addSystemStatus,
    findSystemStatus: findSystemStatus,
    findSystemStatusById: findSystemStatusById,
    updateSystemStatus: updateSystemStatus,
    deleteById: deleteById
}

function addSystemStatus(req, res) {
    let systemStatus = req.body
    systemStatusDao.create(systemStatus)
        .then((data) => {
            res.send(data)
        })
        .catch((error) => {
            console.log(error)
        })
}

function findSystemStatusById(req, res) {
    systemStatusDao.findById(req.params.id)
        .then((data) => {
            res.send(data)
        })
        .catch((error) => {
            console.log(error)
        })
}

function deleteById(req, res) {
    systemStatusDao.deleteById(req.params.id)
        .then((data) => {
            res.status(200).json({
                message: "System status deleted successfully",
                systemStatus: data
            })
        })
        .catch((error) => {
            console.log(error)
        })
}

function updateSystemStatus(req, res) {
    systemStatusDao.updateSystemStatus(req.body, req.params.id)
        .then((data) => {
            res.status(200).json({
                message: "System status updated successfully",
                systemStatus: data
            })
        })
        .catch((error) => {
            console.log(error)
        })
}

function findSystemStatus(req, res) {
    systemStatusDao.findAll()
        .then((data) => {
            res.send(data)
        })
        .catch((error) => {
            console.log(error)
        })
}

module.exports = systemStatusController
