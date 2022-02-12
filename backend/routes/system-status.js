const express = require('express')
const router = express.Router()
const systemStatusController = require('../controllers/systemStatus')

router.post('/', systemStatusController.addSystemStatus)
router.get('/', systemStatusController.findSystemStatus)
router.get('/:id', systemStatusController.findSystemStatusById)
router.put('/:id', systemStatusController.updateSystemStatus)
router.delete('/:id', systemStatusController.deleteById)

module.exports = router
