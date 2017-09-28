/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50714
Source Host           : localhost:3306
Source Database       : vnc

Target Server Type    : MYSQL
Target Server Version : 50714
File Encoding         : 65001

Date: 2017-09-27 23:09:33
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for admin_members
-- ----------------------------
DROP TABLE IF EXISTS `admin_members`;
CREATE TABLE `admin_members` (
  `id` varchar(30) NOT NULL,
  `pw` varchar(255) NOT NULL,
  `intro` varchar(255) DEFAULT NULL,
  `reg_time` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of admin_members
-- ----------------------------
INSERT INTO `admin_members` VALUES ('root', 'dc76e9f0c0006e8f919e0c515c66dbba3982f785', '初始管理员', '2017-09-20 15:44:18');

-- ----------------------------
-- Table structure for file
-- ----------------------------
DROP TABLE IF EXISTS `file`;
CREATE TABLE `file` (
  `name` varchar(255) NOT NULL,
  `time` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  `upload_id` varchar(30) NOT NULL,
  `random_name` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of file
-- ----------------------------

-- ----------------------------
-- Table structure for members
-- ----------------------------
DROP TABLE IF EXISTS `members`;
CREATE TABLE `members` (
  `id` varchar(30) NOT NULL,
  `pw` varchar(256) NOT NULL,
  `intro` varchar(255) DEFAULT NULL,
  `reg_time` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of members
-- ----------------------------
