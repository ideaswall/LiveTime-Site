<?php

/**
 * service for broadcast.
 * @return  JSON
 */
function service_resource_broadcast_index() {
	header('Content-Type: application/json');
	
	$nids = db_query("SELECT nid FROM node WHERE type = 'broadcast' ORDER BY created DESC")->fetchAll();

	if ($nids == NULL) {
		echo json_encode(array('status' => 'false', 'content' => '没有视频信息'));exit;
	}
	$index = 0;
	foreach ($nids as $key => $value) {
		$node = node_load($value->nid);
		$term = taxonomy_term_load($node->field_broadcast_type['und'][0]['tid']);

		$Broadcast[$index++] = array(
			'name' => $node->title,
			'roomNO' => $node->nid,
			'uid' => $node->uid,
			'broadcastType' => $term->name,
		);
	}
	// print_r($Broadcast);exit;
	echo json_encode(array('status' => 'true', 'content' => $Broadcast));
}

/**
 * service for creating new Broadcast.
 * @return  JSON
 */
function service_resource_broadcast_create() {
	header('Content-Type: application/json');

	$name = $_POST['name'];
	$type = $_POST['type'];
	$uid = $_POST['uid'];

	if ($name == NULL || $type == NULL || $uid == NULL) {
		echo json_encode(array('status' => 'false', 'content' => '创建Broadcast出错！'));exit;
	}

	$term = taxonomy_get_term_by_name($type, 'broadcast_type');
	if ($term == NULL) {
		echo json_encode(array('status' => 'false', 'content' => '没有'.$type.'类型的视频！'));exit;
	}
	foreach ($term as $key => $value) {
		$tid = $value->tid;
	}

	$Broadcast = new stdClass();
	$Broadcast->type = 'broadcast';
	$Broadcast->language = LANGUAGE_NONE;
	$Broadcast->status = 1;

	$Broadcast->title = $name;
	$Broadcast->field_broadcast_type['und'][0]['tid'] = $tid;
			
	node_object_prepare($Broadcast);
	if($Broadcast = node_submit($Broadcast)) { 
	  $Broadcast->uid = $uid;
		node_save($Broadcast);
	}
	
	echo json_encode(array('status' => 'true', 'content' => $Broadcast));
}