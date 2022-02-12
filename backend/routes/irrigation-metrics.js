const express = require('express')
const router = express.Router()
const irrigationMetricsController = require('../controllers/irrigationMetrics')

router.post('/', irrigationMetricsController.addIrrigationMetrics)
router.get('/', irrigationMetricsController.findIrrigationMetrics)
router.get('/:id', irrigationMetricsController.findIrrigationMetricsById)
router.put('/:id', irrigationMetricsController.updateIrrigationMetrics)
router.delete('/:id', irrigationMetricsController.deleteById)

module.exports = router
