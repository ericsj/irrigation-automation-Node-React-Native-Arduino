const systemStatus = (sequelize, DataTypes) => {
  const SystemStatus = sequelize.define('SystemStatus', {
    id: {
      type: DataTypes.INTEGER,
      autoIncrement: true,
      allowNull: false,
      primaryKey: true
    },
    status: {
      type: DataTypes.STRING
    }
  })
  return SystemStatus
}

module.exports = systemStatus
