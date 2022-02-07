const systemStatus = (sequelize, DataTypes) => {
  const SystemStatus = sequelize.define('SystemStatus', {
    status: {
      type: DataTypes.STRING
    }
  })
  return SystemStatus
}

module.exports = systemStatus
