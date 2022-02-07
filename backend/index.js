const express = require('express')
const cors = require('cors')
const irrigationMetrics = require('./routes/irrigation-metrics')
const systemStatus = require('./routes/system-status')
const { sequelize } = require('./models')

const app = express()
app.use(express.json())
app.use(cors())

app.use('/api/irrigation-metrics', irrigationMetrics)
app.use('/api/system-status', systemStatus)

sequelize.sync().then(() => {
  console.log('Connected with db')
})

app.listen(5000, () => {
  console.log('Server up and running on port 5000')
})
