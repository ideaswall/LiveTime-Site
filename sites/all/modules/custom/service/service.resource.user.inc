<?php

/**
 * @file
 * Reource functions for services api of LiveTime.
 */


/**
 * User login api
 * 
 */
function service_resource_user_login() {

	include_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'service') . '/service.helper.inc';

	header('Content-Type: application/json');

	$mail = $_POST['mail'];
	$password = $_POST['password'];

	if (!isset($mail) || !isset($password)) {
		echo json_encode(array('status' => 'false', 'content' => '请输入用户名和密码.'));exit;
	}

	// get account with mail
    if ($account = user_load_by_mail($mail)) {

        require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
        // check the pass
        if (user_check_password($password, $account)) {
            
            $user = new stdClass();
            $user->mail = $account->mail;
            $user->uid = $account->uid;
            echo json_encode(array('status' => 'true', 'content' => $user));exit;
        } else {

            echo json_encode(array('status' => 'false', 'content' => '用户名或密码输入错误.'));exit;
        }
    } else {

        echo json_encode(array('status' => 'false', 'content' => '用户名不存在.'));exit;
    }
}

/**
 * User signup api
 * 
 */
function service_resource_user_signup() {

	include_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'service') . '/service.helper.inc';

	service_response_header();

	$mail = $_POST['mail'];
	$password = $_POST['password'];

	if (!isset($mail) || !isset($password)) {
		echo json_encode(array('status' => 'false', 'content' => '请输入用户名和密码.'));exit;
	}


	if ($account = user_load_by_mail($mail)) {

		echo json_encode(array('status' => 'false', 'content' => '用户已存在，请尝试登录.'));exit;
	}
	else {
		// Strip off everything after the @ sign.
		$name = preg_replace('/@.*$/', '', $mail);
		$account = user_save('', array('name'=> $name, 'mail' => $mail, 'pass' => $password, 'status' => 1));

		echo json_encode(array('status' => 'true', 'content' => $account));exit;
	}
}
