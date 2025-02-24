/// @file controllers.js
/// @brief AngularJS controllers

angular.module('myAppControllers', ['ngCookies'])
  .controller('mainController',
    ['$scope',
      '$translate',
      '$location',
      function ($scope, $translate, $location) {
        $scope.data = {
          selectedAssemblyMode: null,
          availableAssemblyModes: [
            {id: 'short_reads_assembling', name: 'SHORT_READS_ASSEMBLY'},
            {id: 'long_reads_assembling', name: 'LONG_READS_ASSEMBLY'},
            {id: 'long_reads_assembling_2', name: 'LONG_READS_ASSEMBLY_2'}
          ]
        };
      }])
  .controller('assemblingController',
    ['$scope',
      '$translate',
      '$location',
      'srvAssembling',
      'srvScaffolding',
      'defaultValues',
      'srvFiles',
      'srvUsers',
      function ($scope, $translate, $location, srvAssembling, srvScaffolding, defaultValues, srvFiles, srvUsers) {

        var initUserMail = function () {
          srvUsers.getUserMail(
            function (data) {
              $scope.addTask_assemblyMailAddress = data;
              $scope.updateTask_assemblyMailAddress = data;
            });
        };
        initUserMail();

        $scope.parseDate = function (id, inputDate, outputDate) {
          var inDate = '', outDate = '';
          if (inputDate != '') {
            inDate = new Date(inputDate).toString();
          }
          if (outputDate != '') {
            outDate = new Date(outputDate).toString();
          }
          document.getElementById('inputTime' + id).innerHTML = inDate.substring(0, inDate.indexOf("GMT"));
          document.getElementById('outputTime' + id).innerHTML = outDate.substring(0, outDate.indexOf("GMT"));
        };

        $scope.parsePairedReadsAlgorithm = function (id, pairedReadsAlgorithm, insertSizeMeanInward, insertSizeStdDevInward, insertSizeMeanOutward, insertSizeStdDevOutward, pairedReadsPetThresholdFrom, pairedReadsPetThresholdTo, pairedReadsMpThresholdFrom, pairedReadsMpThresholdTo) {
          if (pairedReadsAlgorithm == '0') {
            document.getElementById('insertSizeMeanInward' + id).innerHTML = '-';
            document.getElementById('insertSizeStdDevInward' + id).innerHTML = '-';
            document.getElementById('insertSizeMeanOutward' + id).innerHTML = '-';
            document.getElementById('insertSizeStdDevOutward' + id).innerHTML = '-';
            document.getElementById('pairedReadsPetThresholdFrom' + id).innerHTML = '-';
            document.getElementById('pairedReadsPetThresholdTo' + id).innerHTML = '-';
            document.getElementById('pairedReadsMpThresholdFrom' + id).innerHTML = '-';
            document.getElementById('pairedReadsMpThresholdTo' + id).innerHTML = '-';
            document.getElementById('pairedReadsAlgorithm' + id).innerHTML = '-';
          } else if (pairedReadsAlgorithm == '1') {
            document.getElementById('insertSizeMeanInward' + id).innerHTML = insertSizeMeanInward;
            document.getElementById('insertSizeStdDevInward' + id).innerHTML = insertSizeStdDevInward;
            document.getElementById('insertSizeMeanOutward' + id).innerHTML = insertSizeMeanOutward;
            document.getElementById('insertSizeStdDevOutward' + id).innerHTML = insertSizeStdDevOutward;
            document.getElementById('pairedReadsPetThresholdFrom' + id).innerHTML = pairedReadsPetThresholdFrom;
            document.getElementById('pairedReadsPetThresholdTo' + id).innerHTML = pairedReadsPetThresholdTo;
            document.getElementById('pairedReadsMpThresholdFrom' + id).innerHTML = pairedReadsMpThresholdFrom;
            document.getElementById('pairedReadsMpThresholdTo' + id).innerHTML = pairedReadsMpThresholdTo;
            document.getElementById('pairedReadsAlgorithm' + id).innerHTML = '1';
          }
        };

        $scope.parseFileName = function (id, i1_1_file_name, i1_2_file_name, o1_1_file_name, o1_2_file_name) {
          var i1_1_name = '-', i1_2_name = '-', o1_1_name = '-', o1_2_name = '-';
          if (i1_1_file_name != '') {
            i1_1_name = i1_1_file_name;
          }
          if (i1_2_file_name != '') {
            i1_2_name = i1_2_file_name;
          }
          if (o1_1_file_name != '') {
            o1_1_name = o1_1_file_name;
          }
          if (o1_2_file_name != '') {
            o1_2_name = o1_2_file_name;
          }
          document.getElementById('i1_1_file_name' + id).innerHTML = i1_1_name;
          document.getElementById('i1_2_file_name' + id).innerHTML = i1_2_name;
          document.getElementById('o1_1_file_name' + id).innerHTML = o1_1_name;
          document.getElementById('o1_2_file_name' + id).innerHTML = o1_2_name;
        };

        $scope.insertSizeMeanInwardDisable = true;
        $scope.insertSizeStdDevInwardDisable = true;
        $scope.insertSizeMeanOutwardDisable = true;
        $scope.insertSizeStdDevOutwardDisable = true;
        $scope.pairedEdgeConterThresholdDisable = true;
        $scope.pairedReadsPetThresholdFromDisable = true;
        $scope.pairedReadsPetThresholdToDisable = true;
        $scope.pairedReadsMpThresholdFromDisable = true;
        $scope.pairedReadsMpThresholdToDisable = true;
        $scope.addInsertSizeMeanInward = "-";
        $scope.addInsertSizeStdDevInward = "-";
        $scope.addInsertSizeMeanOutward = "-";
        $scope.addInsertSizeStdDevOutward = "-";
        $scope.addPairedReadsPetThresholdFrom = "-";
        $scope.addPairedReadsPetThresholdTo = "-";
        $scope.addPairedReadsMpThresholdFrom = "-";
        $scope.addPairedReadsMpThresholdTo = "-";
        $scope.addPairedReadsAlgorithmChange = function () {
          if (document.getElementById('addPairedReadsAlgorithm').value == "0") {
            $scope.insertSizeMeanInwardDisable = true;
            $scope.insertSizeStdDevInwardDisable = true;
            $scope.insertSizeMeanOutwardDisable = true;
            $scope.insertSizeStdDevOutwardDisable = true;
            $scope.pairedEdgeConterThresholdDisable = true;
            $scope.pairedReadsPetThresholdFromDisable = true;
            $scope.pairedReadsPetThresholdToDisable = true;
            $scope.pairedReadsMpThresholdFromDisable = true;
            $scope.pairedReadsMpThresholdToDisable = true;
            $scope.addInsertSizeMeanInward = "-";
            $scope.addInsertSizeStdDevInward = "-";
            $scope.addInsertSizeMeanOutward = "-";
            $scope.addInsertSizeStdDevOutward = "-";
            $scope.addPairedReadsPetThresholdFrom = "-";
            $scope.addPairedReadsPetThresholdTo = "-";
            $scope.addPairedReadsMpThresholdFrom = "-";
            $scope.addPairedReadsMpThresholdTo = "-";
          } else {
            $scope.insertSizeMeanInwardDisable = false;
            $scope.insertSizeStdDevInwardDisable = false;
            $scope.insertSizeMeanOutwardDisable = false;
            $scope.insertSizeStdDevOutwardDisable = false;
            $scope.pairedEdgeConterThresholdDisable = true;
            $scope.pairedReadsPetThresholdFromDisable = false;
            $scope.pairedReadsPetThresholdToDisable = false;
            $scope.pairedReadsMpThresholdFromDisable = false;
            $scope.pairedReadsMpThresholdToDisable = false;
            $scope.addInsertSizeMeanInward = defaultValues.getDefaultValues().insertSizeMeanInward;
            $scope.addInsertSizeStdDevInward = defaultValues.getDefaultValues().insertSizeStdDevInward;
            $scope.addInsertSizeMeanOutward = defaultValues.getDefaultValues().insertSizeMeanOutward;
            $scope.addInsertSizeStdDevOutward = defaultValues.getDefaultValues().insertSizeStdDevOutward;
            $scope.addPairedReadsPetThresholdFrom = defaultValues.getDefaultValues().pairedReadsPetThresholdFrom;
            $scope.addPairedReadsPetThresholdTo = defaultValues.getDefaultValues().pairedReadsPetThresholdTo;
            $scope.addPairedReadsMpThresholdFrom = defaultValues.getDefaultValues().pairedReadsMpThresholdFrom;
            $scope.addPairedReadsMpThresholdTo = defaultValues.getDefaultValues().pairedReadsMpThresholdTo;
          }
        };

        $scope.addVar = false;
        $scope.addVarChange = function () {
          $scope.addVar = !$scope.addVar;
        };
        $scope.addK = defaultValues.getDefaultValues().k;
        $scope.addT = defaultValues.getDefaultValues().T;
        $scope.addGenomeLength = defaultValues.getDefaultValues().genomeLength;
        $scope.addBfcounterThreshold = defaultValues.getDefaultValues().bfcounterThreshold;
        $scope.addSingleEdgeCounterThreshold = defaultValues.getDefaultValues().singleEdgeCounterThreshold;

        $scope.addKmerSize = defaultValues.getDefaultValues().kmerSize;
        $scope.addDistance = defaultValues.getDefaultValues().distance;
        $scope.addStep = defaultValues.getDefaultValues().step;
        $scope.addMinLinks = defaultValues.getDefaultValues().minLinks;
        $scope.addMaxRatio = defaultValues.getDefaultValues().maxRatio;
        $scope.addMinContigLength = defaultValues.getDefaultValues().minContigLength;
        $scope.addTask = function (data) {
          var RE = /^[0-9]+$/;
          if (document.getElementById('assemblyModeSelect').value === 'short_reads_assembling') {
            if (document.getElementById('addTaskName').value != "" &&
              document.getElementById('addK').value.match(RE) &&
              document.getElementById('addT').value.match(RE) &&
              document.getElementById('addGenomeLength').value.match(RE) &&
              document.getElementById('addBfcounterThreshold').value.match(RE) &&
              document.getElementById('addSingleEdgeCounterThreshold').value.match(RE) &&
              (document.getElementById('add_i1_1').value != "" || document.getElementById('add_i1_2').value != "" ||
                document.getElementById('add_o1_1').value != "" || document.getElementById('add_o1_2').value != "")) {
              srvAssembling.addTask(
                function (data) {
                  if (data.status == 'error' && data.msg == 'Task name error.') {
                    alert($translate.instant('TASK_NAME_ERROR'));
                  } else if (data.status == 'success' && document.getElementById('addTask_assemblyShowResultUrlCheckbox').checked) {
                    alert($translate.instant('DOWNLOAD_RESULT_FROM') + '\n\n' + data.result_url);
                  }
                }
              );

              var RE = /^-?\d+(.\d+)?$/
              if (document.getElementById('addTask_generateScaffoldCheckbox').checked
                && document.getElementById('addKmerSize').value.match(RE)
                && document.getElementById('addDistance').value.match(RE)
                && document.getElementById('addStep').value.match(RE)
                && document.getElementById('addMinLinks').value.match(RE)
                && document.getElementById('addMaxRatio').value.match(RE)
                && document.getElementById('addMinContigLength').value.match(RE)
                && document.getElementById('add_long_reads').value != "") {
                console.log('creating s task with name: ', document.getElementById('addTaskName').value + '_scaffold');
                srvScaffolding.addDelayedScaffoldTask(
                  document.getElementById('addTaskName').value + '_scaffold',
                  document.getElementById('addTaskName').value,
                  function (data) {
                    if (data.status == 'error' && data.msg == 'Task name error.') {
                      alert($translate.instant('TASK_NAME_ERROR'));
                    }
                  }
                );
              }

              document.getElementById('addTaskName').value = "";
              document.getElementById('addCorrect').checked = true;
              document.getElementById('add_i1_1').value = "";
              document.getElementById('add_i1_2').value = "";
              document.getElementById('add_o1_1').value = "";
              document.getElementById('add_o1_2').value = "";
              $scope.addVar = false;
            }
          } else if (document.getElementById('assemblyModeSelect').value === 'long_reads_assembling') {
            srvAssembling.addTask(
              function (data) {
                if (data.status == 'error' && data.msg == 'Task name error.') {
                  alert($translate.instant('TASK_NAME_ERROR'));
                } else if (data.status == 'success' && document.getElementById('addTask_assemblyShowResultUrlCheckbox').checked) {
                  alert($translate.instant('DOWNLOAD_RESULT_FROM') + '\n\n' + data.result_url);
                }
              }
            );
          }
        };
        $scope.deleteTask = function (task) {
          if (task.state == 'PENDING' || task.state == 'QUEUED' || task.state == 'NONE') {
            alert($translate.instant('DELETE_WHILE_PENDING_TASK_ERROR'));
            return;
          }
          srvAssembling.deleteTask(task.id);
        };

        $scope.breakTask = function (taskId) {
          srvAssembling.breakTask(taskId);
        };

        $scope.actualTaskId = 0;
        $scope.updateVar = false;
        $scope.updateTask = function (data) {
          srvAssembling.updateTask($scope.actualTaskId,
            function (data) {
              if (data.status == 'error' && data.msg == 'Task name error.') {
                alert($translate.instant('TASK_NAME_ERROR'));
              } else if (data.status == 'success' && document.getElementById('updateTask_assemblyShowResultUrlCheckbox').checked) {
                alert($translate.instant('DOWNLOAD_RESULT_FROM') + '\n\n' + data.result_url);
              }
            });
          $scope.updateVar = false;
        };
        $scope.update = function (row) {
          if (row.state == 'PENDING' || row.state == 'QUEUED' || row.state == 'NONE' || row.state == 'INTERRUPTED' || row.state == 'EXCEPTION') {
            alert($translate.instant('UPDATE_WHILE_PENDING_TASK_ERROR'));
            return;
          }
          if ($scope.updateVar == false) {
            $scope.updateVar = true;
          }
          $scope.actualTaskId = row.id;
          document.getElementById('updateK').value = row.k;
          document.getElementById('updateGenomeLength').value = row.genome_length;
          document.getElementById('updateInsertSizeMeanInward').value = row.insert_size_mean_inward;
          document.getElementById('updateInsertSizeStdDevInward').value = row.insert_size_std_dev_inward;
          document.getElementById('updateInsertSizeMeanOutward').value = row.insert_size_mean_outward;
          document.getElementById('updateInsertSizeStdDevOutward').value = row.insert_size_std_dev_outward;
          document.getElementById('updateT').value = row.quality_threshold;
          document.getElementById('updateBfcounterThreshold').value = row.bfcounter_threshold;
          document.getElementById('updateSingleEdgeCounterThreshold').value = row.single_edge_counter_threshold;
          document.getElementById('updatePairedReadsPetThresholdFrom').value = row.paired_reads_pet_threshold_from;
          document.getElementById('updatePairedReadsPetThresholdTo').value = row.paired_reads_pet_threshold_to;
          document.getElementById('updatePairedReadsMpThresholdFrom').value = row.paired_reads_mp_threshold_from;
          document.getElementById('updatePairedReadsMpThresholdTo').value = row.paired_reads_mp_threshold_to;
          if (row.correct)
            document.getElementById('updateCorrect').checked = true;
          else
            document.getElementById('updateCorrect').checked = false;
          if (row.paired_reads_algorithm == "0")
            document.getElementById('updatePairedReadsAlgorithm').options[0].selected = "selected";
          else
            document.getElementById('updatePairedReadsAlgorithm').options[1].selected = "selected";
          document.getElementById('update_i1_1').value = row.i1_1_file_name;
          document.getElementById('update_i1_2').value = row.i1_2_file_name;
          document.getElementById('update_o1_1').value = row.o1_1_file_name;
          document.getElementById('update_o1_2').value = row.o1_2_file_name;
        };

        $scope.downloadAssemblyTaskResult = function (taskId) {
          $scope.currentTab = '/files';
          $location.path('/files');
          srvAssembling.getAssemblyTaskDocfile(taskId,
            function (data) {
              srvFiles.downloadFile(data.docfile, data.file_name);
            }
          );
        };

        $scope.seeAssemblyTaskResult = function (taskId) {
          srvAssembling.getAssemblyTaskDocfile(taskId,
            function (data) {
              srvFiles.getFileContents(
                data.docfile, function (data) {
                  if (data.status == 'error' && data.msg == 'File does not exist.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_NOT_EXIST'));
                    return;
                  }
                  if (data.status == 'error' && data.msg == 'File is oversized.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_IS_OVERSIZED'));
                    return;
                  }
                  var fileContents = data.msg;
                  fileContents = fileContents.replace(/\n/g, "<br />");
                  var newWindow = window.open("", "", "");
                  newWindow.document.writeln(fileContents);
                });
            }
          );
        };
      }])
  .controller('allAssemblingController',
    ['$scope',
      '$timeout',
      '$interval',
      'srvAllAssembling',
      function ($scope, $timeout, $interval, srvAllAssembling) {
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvAllAssembling.getAllAssemblyTasks(
            function (data) {
              $scope.all_assembling_tasks = data;
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('userAssemblingController',
    ['$scope',
      '$timeout',
      '$interval',
      'defaultValues',
      'srvUserAssembling',
      function ($scope, $timeout, $interval, defaultValues, srvUserAssembling) {
        $scope.addTask_assemblyResultNotificationCheckbox = defaultValues.getDefaultValues().assemblyResultNotification;
        $scope.updateTask_assemblyResultNotificationCheckbox = defaultValues.getDefaultValues().assemblyResultNotification;
        //document.getElementById('addTask_assemblyShowResultUrlCheckbox').checked = defaultValues.getDefaultValues().assemblyShowResultUrl;
        //document.getElementById('updateTask_assemblyShowResultUrlCheckbox').checked = defaultValues.getDefaultValues().assemblyShowResultUrl;
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvUserAssembling.getUserAssemblyTasks(
            function (data) {
              $scope.user_assembling_tasks = data;
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('tabsController',
    ['$scope',
      '$cookieStore',
      '$location',
      function ($scope, $cookieStore, $location) {
        $scope.user_tabs = [{
          title: 'ASSEMBLING',
          url: '/assembling'
        }, {
          title: 'SCAFFOLDING',
          url: '/scaffolding'
        }, {
          title: 'ALIGNMENT',
          url: '/alignment'
        }, {
          title: 'FILES',
          url: '/files'
        }, {
          title: 'SETTINGS',
          url: '/settings'
        }];
        $scope.admin_tabs = [{
          title: 'USERS',
          url: '/users'
        }, {
          title: 'ALL_FILES',
          url: '/all_files'
        }, {
          title: 'ALL_JOBS',
          url: '/all_jobs'
        }];
        $scope.isUserLoggedIn = function (data) {
          if ($scope.currentTab == '/assembling' && $cookieStore.get('isLogged') && $location.path() != '/help' && $location.path() != '/file_formats' && $location.path() != '/algorithms' && $location.path() != '/files') {
            $location.path('/assembling');
          }
          if (!$cookieStore.get('isLogged') && $location.path() != '/help' && $location.path() != '/file_formats' && $location.path() != '/algorithms') {
            $scope.currentTab = '/assembling';
            $location.path('/start_page');
          }
          return $cookieStore.get('isLogged');
        };
        $scope.isSuperuser = function (data) {
          return $cookieStore.get('isSuperuser');
        };
        $scope.onClickTab = function (tab) {
          $scope.currentTab = tab.url;
          $location.path(tab.url);
        }
        $scope.isActiveTab = function (tabUrl) {
          return tabUrl == $scope.currentTab;
        }
      }])
  .controller('helpPageController',
    ['$scope',
      '$location',
      function ($scope, $location) {
        $scope.openHelpWindow = function () {
          $location.path('/help');
        }
      }])
  .controller('filesController',
    ['$scope',
      '$translate',
      'srvFiles',
      function ($scope, $translate, srvFiles) {
        $scope.parseDate = function (fileName, inputDate) {
          var inDate = '';
          if (inputDate != '') {
            inDate = new Date(inputDate).toString();
          }
          document.getElementById('inputTime_' + fileName).innerHTML = inDate.substring(0, inDate.indexOf("GMT"));
        };
        $scope.seeFileContents = function (docfile, isVCF) {
          srvFiles.getFileContents(
            docfile, function (data) {
              if (data.status == 'error' && data.msg == 'File does not exist.') {
                alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_NOT_EXIST'));
                return;
              }
              if (data.status == 'error' && data.msg == 'File is oversized.') {
                alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_IS_OVERSIZED'));
                return;
              }
              var fileContents = data.msg;
              if (isVCF == true) {
                fileContents = fileContents.replace(/\n/g, "</td></tr><tr><td>");
                fileContents = fileContents.replace("</td></tr><tr><td>#CHROM", "<br><table><tr><td>#CHROM");
                fileContents = fileContents.replace(/\t/g, "</td><td>");
                fileContents = fileContents.replace("</td></tr><tr><table>", "<table>");
                fileContents = fileContents + "</table>";
                fileContents = fileContents.replace("<tr></table>", "</table>");
              } else {
                fileContents = fileContents.replace(/\n/g, "<br />");
              }
              var newWindow = window.open("", "", "");
              newWindow.document.writeln(fileContents);
            });
        };
        $scope.uploadFile = function () {
          var file = document.getElementById('chooseUploadFile').files[0];
          if (file != undefined) {
            srvFiles.uploadFile(file);
            document.getElementById('chooseUploadFile').value = '';
            document.getElementById('uploadFile').disabled = true;
            document.getElementById('chooseUploadFile').disabled = true;
          }
        };
        $scope.uploadExampleFiles = function () {
          srvFiles.uploadExampleFiles();
        };
        $scope.deleteFile = function (docfile) {
          if (document.getElementById('downloadProgress_' + docfile).innerHTML != '') {
            alert($translate.instant('DELETE_WHILE_DOWNLOADING_FILE_ERROR'));
            return;
          }
          srvFiles.deleteFile(docfile,
            function (data) {
              if (data.status == 'error') {
                alert($translate.instant('DELETE_FILE_ERROR'));
              }
            });
        };
        $scope.downloadFile = function (docfile, fileName) {
          if (document.getElementById('downloadProgress_' + docfile).innerHTML != '') {
            alert($translate.instant('DOUBLE_DOWNLOAD_ERROR'));
            return;
          }
          srvFiles.downloadFile(docfile, fileName);
        };
      }])
  .controller('allFilesController',
    ['$scope',
      '$timeout',
      '$interval',
      'srvFiles',
      'srvSplitFiles',
      function ($scope, $timeout, $interval, srvFiles, srvSplitFiles) {
        $scope.all_files_fasta = [];
        $scope.all_files_fastq = [];
        $scope.all_files_vcf = [];
        $scope.all_files_unknown = [];
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvFiles.getAllFiles(
            function (data) {
              srvFiles.getAllFiles(
                function (data) {
                  srvSplitFiles.splitFiles(data,
                    function (data) {
                      $scope.all_files_fasta = data.files_fasta;
                      $scope.all_files_fastq = data.files_fastq;
                      $scope.all_files_vcf = data.files_vcf;
                      $scope.all_files_unknown = data.files_unknown;
                    });
                });
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('userFilesController',
    ['$scope',
      '$timeout',
      '$interval',
      'srvFiles',
      'srvSplitFiles',
      function ($scope, $timeout, $interval, srvFiles, srvSplitFiles) {
        $scope.user_files_fasta = [];
        $scope.user_files_fastq = [];
        $scope.user_files_vcf = [];
        $scope.user_files_unknown = [];
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvFiles.getUserFiles(
            function (data) {
              srvFiles.getUserFiles(
                function (data) {
                  srvSplitFiles.splitFiles(data,
                    function (data) {
                      $scope.user_files_fasta = data.files_fasta;
                      $scope.user_files_fastq = data.files_fastq;
                      $scope.user_files_vcf = data.files_vcf;
                      $scope.user_files_unknown = data.files_unknown;
                    });
                });
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('alignmentController',
    ['$scope',
      '$translate',
      '$location',
      'defaultValues',
      'srvAlignment',
      'srvFiles',
      'srvUsers',
      function ($scope, $translate, $location, defaultValues, srvAlignment, srvFiles, srvUsers) {
        $scope.gapPenalty = defaultValues.getDefaultValues().gapPenalty;
        $scope.AA = defaultValues.getDefaultValues().AA;
        $scope.AC = defaultValues.getDefaultValues().AC;
        $scope.AG = defaultValues.getDefaultValues().AG;
        $scope.AT = defaultValues.getDefaultValues().AT;
        $scope.CA = defaultValues.getDefaultValues().CA;
        $scope.CC = defaultValues.getDefaultValues().CC;
        $scope.CG = defaultValues.getDefaultValues().CG;
        $scope.CT = defaultValues.getDefaultValues().CT;
        $scope.GA = defaultValues.getDefaultValues().GA;
        $scope.GC = defaultValues.getDefaultValues().GC;
        $scope.GG = defaultValues.getDefaultValues().GG;
        $scope.GT = defaultValues.getDefaultValues().GT;
        $scope.TA = defaultValues.getDefaultValues().TA;
        $scope.TC = defaultValues.getDefaultValues().TC;
        $scope.TG = defaultValues.getDefaultValues().TG;
        $scope.TT = defaultValues.getDefaultValues().TT;

        var initUserMail = function () {
          srvUsers.getUserMail(
            function (data) {
              $scope.alignMailAddress = data;
            });
        };
        initUserMail();

        $scope.align = function () {
          var RE = /^-?\d+$/;
          if (document.getElementById('newAlignTaskName').value != "" && document.getElementById('gapPenalty').value.match(RE) && document.getElementById('AA').value.match(RE) && document.getElementById('AC').value.match(RE) && document.getElementById('AG').value.match(RE) && document.getElementById('AT').value.match(RE) && document.getElementById('CA').value.match(RE) && document.getElementById('CC').value.match(RE) && document.getElementById('CG').value.match(RE) && document.getElementById('CT').value.match(RE) && document.getElementById('GA').value.match(RE) && document.getElementById('GC').value.match(RE) && document.getElementById('GG').value.match(RE) && document.getElementById('GT').value.match(RE) && document.getElementById('TA').value.match(RE) && document.getElementById('TC').value.match(RE) && document.getElementById('TG').value.match(RE) && document.getElementById('TT').value.match(RE)) {
            srvAlignment.alignSequence(
              function (data) {
                if (data.status == 'error' && data.msg == 'Task name error.') {
                  alert($translate.instant('TASK_NAME_ERROR'));
                } else if (data.status == 'success' && document.getElementById('alignShowResultUrlCheckbox').checked) {
                  alert($translate.instant('DOWNLOAD_RESULT_FROM') + '\n\n' + data.result_url);
                }
              }
            );
          }
        };

        $scope.parseDate = function (id, inputDate, outputDate) {
          var inDate = '', outDate = '';
          if (inputDate != '') {
            inDate = new Date(inputDate).toString();
          }
          if (outputDate != '') {
            outDate = new Date(outputDate).toString();
          }
          document.getElementById('alignTask_inputTime' + id).innerHTML = inDate.substring(0, inDate.indexOf("GMT"));
          document.getElementById('alignTask_outputTime' + id).innerHTML = outDate.substring(0, outDate.indexOf("GMT"));
        };

        $scope.deleteAlignTask = function (task) {
          if (task.state == 'PENDING' || task.state == 'QUEUED' || task.state == 'NONE') {
            alert($translate.instant('DELETE_WHILE_PENDING_TASK_ERROR'));
            return;
          }
          srvAlignment.deleteAlignTask(task.id);
        };

        $scope.breakAlignTask = function (taskId) {
          srvAlignment.breakAlignTask(taskId);
        };

        $scope.seeAlignTaskResult = function (taskId) {
          srvAlignment.getAlignTaskDocfile(taskId,
            function (data) {
              srvFiles.getFileContents(
                data.docfile, function (data) {
                  if (data.status == 'error' && data.msg == 'File does not exist.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_NOT_EXIST'));
                    return;
                  }
                  if (data.status == 'error' && data.msg == 'File is oversized.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_IS_OVERSIZED'));
                    return;
                  }
                  var fileContents = data.msg;
                  fileContents = fileContents.replace(/\n/g, "</td></tr><tr><td>");
                  fileContents = fileContents.replace("</td></tr><tr><td>#CHROM", "<br><table><tr><td>#CHROM");
                  fileContents = fileContents.replace(/\t/g, "</td><td>");
                  fileContents = fileContents.replace("</td></tr><tr><table>", "<table>");
                  fileContents = fileContents + "</table>";
                  fileContents = fileContents.replace("<tr></table>", "</table>");
                  var newWindow = window.open("", "", "");
                  newWindow.document.writeln(fileContents);
                });
            }
          );
        };

        $scope.downloadAlignTaskResult = function (taskId) {
          $location.path('/files');
          $scope.currentTab = '/files';
          srvAlignment.getAlignTaskDocfile(taskId,
            function (data) {
              srvFiles.downloadFile(data.docfile, data.file_name);
            }
          );
        };
      }])
  .controller('allAlignmentController',
    ['$scope',
      '$timeout',
      '$interval',
      'srvAllAlignment',
      function ($scope, $timeout, $interval, srvAllAlignment) {
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvAllAlignment.getAllAlignTasks(
            function (data) {
              $scope.all_align_tasks = data;
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('userAlignmentController',
    ['$scope',
      '$timeout',
      '$interval',
      'defaultValues',
      'srvUserAlignment',
      function ($scope, $timeout, $interval, defaultValues, srvUserAlignment) {
        document.getElementById('alignAlgorithmSelect').value = defaultValues.getDefaultValues().alignAlgorithm;
        document.getElementById('circularCheckbox').checked = defaultValues.getDefaultValues().isCircular;
        $scope.alignResultNotificationCheckbox = defaultValues.getDefaultValues().alignResultNotification;
        document.getElementById('alignShowResultUrlCheckbox').checked = defaultValues.getDefaultValues().alignShowResultUrl;
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvUserAlignment.getUserAlignTasks(
            function (data) {
              $scope.user_align_tasks = data;
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('scaffoldingController',
    ['$scope',
      '$translate',
      '$location',
      'defaultValues',
      'srvFiles',
      'srvScaffolding',
      function ($scope, $translate, $location, defaultValues, srvFiles, srvScaffolding) {
        $scope.kmerSize = defaultValues.getDefaultValues().kmerSize;
        $scope.distance = defaultValues.getDefaultValues().distance;
        $scope.step = defaultValues.getDefaultValues().step;
        $scope.minLinks = defaultValues.getDefaultValues().minLinks;
        $scope.maxRatio = defaultValues.getDefaultValues().maxRatio;
        $scope.minContigLength = defaultValues.getDefaultValues().minContigLength;

        $scope.scaffold = function () {
          var RE = /^-?\d+(.\d+)?$/;
          if (document.getElementById('newScaffoldTaskName').value != ""
            && document.getElementById('longReadsFile').value != ""
            && document.getElementById('kmerSize').value.match(RE)
            && document.getElementById('distance').value.match(RE)
            && document.getElementById('step').value.match(RE)
            && document.getElementById('minLinks').value.match(RE)
            && document.getElementById('maxRatio').value.match(RE)
            && document.getElementById('minContigLength').value.match(RE)) {
            srvScaffolding.addScaffoldTask(
              function (data) {
                if (data.status == 'error' && data.msg == 'Task name error.') {
                  alert($translate.instant('TASK_NAME_ERROR'));
                }
              }
            );
          }
        };

        $scope.parseDate = function (id, inputDate, outputDate) {
          var inDate = '', outDate = '';
          if (inputDate != '') {
            inDate = new Date(inputDate).toString();
          }
          if (outputDate != '') {
            outDate = new Date(outputDate).toString();
          }
          document.getElementById('scaffoldTask_inputTime' + id).innerHTML = inDate.substring(0, inDate.indexOf("GMT"));
          document.getElementById('scaffoldTask_outputTime' + id).innerHTML = outDate.substring(0, outDate.indexOf("GMT"));
        };

        $scope.deleteScaffoldTask = function (task) {
          if (task.state == 'PENDING' || task.state == 'QUEUED' || task.state == 'NONE') {
            alert($translate.instant('DELETE_WHILE_PENDING_TASK_ERROR'));
            return;
          }
          srvScaffolding.deleteScaffoldTask(task.id);
        };

        $scope.breakScaffoldTask = function (taskId) {
          srvScaffolding.breakScaffoldTask(taskId);
        };

        $scope.seeScaffoldTaskResult = function (taskId) {
          srvScaffolding.getScaffoldTaskDocfile(taskId,
            function (data) {
              srvFiles.getFileContents(
                data.docfile, function (data) {
                  if (data.status == 'error' && data.msg == 'File does not exist.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_NOT_EXIST'));
                    return;
                  }
                  if (data.status == 'error' && data.msg == 'File is oversized.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_IS_OVERSIZED'));
                    return;
                  }
                  var fileContents = data.msg;
                  // fileContents = fileContents.replace(/\n/g, "</td></tr><tr><td>");
                  // fileContents = fileContents.replace("</td></tr><tr><td>#CHROM", "<br><table><tr><td>#CHROM");
                  // fileContents = fileContents.replace(/\t/g, "</td><td>");
                  // fileContents = fileContents.replace("</td></tr><tr><table>", "<table>");
                  // fileContents = fileContents + "</table>";
                  // fileContents = fileContents.replace("<tr></table>", "</table>");
                  var newWindow = window.open("", "", "");
                  newWindow.document.writeln(fileContents);
                });
            }
          );
        };

        $scope.downloadScaffoldTaskResult = function (taskId) {
          $location.path('/files');
          $scope.currentTab = '/files';
          srvScaffolding.getScaffoldTaskDocfile(taskId,
            function (data) {
              srvFiles.downloadFile(data.docfile, data.file_name);
            }
          );
        };
      }])
  .controller('allScaffoldingController',
    ['$scope',
      '$timeout',
      '$interval',
      'srvAllScaffolding',
      function ($scope, $timeout, $interval, srvAllScaffolding) {
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvAllScaffolding.getAllScaffoldTasks(
            function (data) {
              $scope.getAllScaffoldTasks = function () {
                srvAllScaffolding.getAllScaffoldTasks(
                  function (data) {
                    $scope.all_scaffold_tasks = data;
                  });
              };
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('userScaffoldingController',
    ['$scope',
      '$timeout',
      '$interval',
      'defaultValues',
      'srvUserScaffolding',
      function ($scope, $timeout, $interval, defaultValues, srvUserScaffolding) {
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvUserScaffolding.getUserScaffoldTasks(
            function (data) {
              srvUserScaffolding.getUserScaffoldTasks(
                function (data) {
                  $scope.user_scaffold_tasks = data;
                });
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('olcController',
    ['$scope',
      '$translate',
      '$location',
      'defaultValues',
      'srvFiles',
      'srvOLC',
      function ($scope, $translate, $location, defaultValues, srvFiles, srvOLC) {
        $scope.params = {}
        //default values initialization
        $scope.params.kmerLength = defaultValues.getDefaultValues().kmerLength;
        $scope.params.sketchNum = defaultValues.getDefaultValues().sketchNum;
        $scope.params.minJaccardSim = defaultValues.getDefaultValues().minJaccardSim;
        $scope.params.matchScore = defaultValues.getDefaultValues().matchScore;
        $scope.params.mismatchScore = defaultValues.getDefaultValues().mismatchScore;
        $scope.params.gapPenalty = defaultValues.getDefaultValues().gapPenalty;
        $scope.params.minEdge = defaultValues.getDefaultValues().minEdge;
        $scope.params.minContigLength = defaultValues.getDefaultValues().minContigLength;
        $scope.params.pathWidth = defaultValues.getDefaultValues().pathWidth;

        $scope.assembly = function () {
          const RE = /^-?\d+(.\d+)?$/;
          if (document.getElementById('newOLCTaskName').value != ""
            && document.getElementById('longReadsFile').value != ""
            && document.getElementById('kmerLength').value.match(RE)
            && document.getElementById('sketchNum').value.match(RE)
            && document.getElementById('minJaccardSim').value.match(RE)
            && document.getElementById('matchScore').value.match(RE)
            && document.getElementById('mismatchScore').value.match(RE)
            && document.getElementById('gapPenalty').value.match(RE)
            && document.getElementById('minEdge').value.match(RE)
            && document.getElementById('minContigLength').value.match(RE)
            && document.getElementById('pathWidth').value.match(RE)) {
            srvOLC.addTask($scope.params,
              function (data) {
                if (data.status == 'error' && data.msg == 'Task name error.') {
                  alert($translate.instant('TASK_NAME_ERROR'));
                }
              }
            );
          }
        };

        $scope.parseDate = function (id, inputDate, outputDate) {
          let inDate = '', outDate = '';
          if (inputDate != '') {
            inDate = new Date(inputDate).toString();
          }
          if (outputDate != '') {
            outDate = new Date(outputDate).toString();
          }
          document.getElementById('olcTask_inputTime' + id).innerHTML = inDate.substring(0, inDate.indexOf("GMT"));
          document.getElementById('olcTask_outputTime' + id).innerHTML = outDate.substring(0, outDate.indexOf("GMT"));
        };

        $scope.deleteOLCTask = function (task) {
          if (task.state == 'PENDING' || task.state == 'QUEUED' || task.state == 'NONE') {
            alert($translate.instant('DELETE_WHILE_PENDING_TASK_ERROR'));
            return;
          }

          srvOLC.deleteOLCTask(task.id);
        };

        $scope.breakOLCTask = function (taskId) {
          srvOLC.breakOLCTask(taskId);
        };

        $scope.seeOLCTaskResult = function (taskId) {
          srvOLC.getOLCaskDocfile(taskId,
            function (data) {
              srvFiles.getFileContents(
                data.docfile, function (data) {
                  if (data.status == 'error' && data.msg == 'File does not exist.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_NOT_EXIST'));
                    return;
                  }

                  if (data.status == 'error' && data.msg == 'File is oversized.') {
                    alert($translate.instant('SEE_FILE_CONTENTS_ERROR_FILE_IS_OVERSIZED'));
                    return;
                  }

                  const fileContents = data.msg;
                  let newWindow = window.open("", "", "");
                  newWindow.document.writeln(fileContents);
                });
            }
          );
        };

        $scope.downloadOLCTaskResult = function (taskId) {
          $location.path('/files');
          $scope.currentTab = '/files';
          srvOLC.getOLCTaskDocfile(taskId,
            function (data) {
              srvFiles.downloadFile(data.docfile, data.file_name);
            }
          );
        };
      }])
  .controller('allOLCController',
    ['$scope',
      '$timeout',
      '$interval',
      'srvAllOLC',
      function ($scope, $timeout, $interval, srvAllOLC) {
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvAllOLC.getAllOLCTasks(
            function (data) {
              $scope.getAllOLCTasks = function () {
                srvAllOLC.getAllOLCTasks(
                  function (data) {
                    $scope.all_olc_tasks = data;
                  });
              };
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('userOLCController',
    ['$scope',
      '$timeout',
      '$interval',
      'defaultValues',
      'srvUserOLC',
      function ($scope, $timeout, $interval, defaultValues, srvUserOLC) {
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvUserOLC.getUserOLCTasks(
            function (data) {
              srvUserOLC.getUserOLCTasks(
                function (data) {
                  $scope.user_olc_tasks = data;
                });
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('bstAssemblingController',
    ['$scope',
      '$translate',
      'srvBstAssembling',
      'srvFiles',
      function ($scope, $translate, srvBstAssembling, srvFiles) {
        $scope.addTask = function (data) {
          srvBstAssembling.addTask($scope.params,
            function (data) {
              $scope.row = angular.copy($scope.params)
              $scope.row.id = data.task_id
              $scope.showTaskTable = true
            }
          )
        };

        $scope.downloadAssemblyTaskResult = function (taskId) {
          srvBstAssembling.getAssemblyTaskDocfile(taskId,
            function (data) {
              srvFiles.downloadFile(data.docfile, data.file_name);
            }
          );
        };
      }])
  .controller('languagesController', //client static settings - language
    ['$scope',
      '$translate',
      function ($scope, $translate) {
        $scope.langs = ['en', 'pl'];
        $scope.changeLanguage = function (lang) {
          $translate.use(lang);
        };
      }])
  .controller('loginController',
    ['$scope',
      '$translate',
      '$cookieStore',
      'ngDialog',
      'srvLogInOut',
      function ($scope, $translate, $cookieStore, ngDialog, srvLogInOut) {
        $scope.isUserLoggedIn = function (data) {
          $scope.username = $cookieStore.get('username');
          return $cookieStore.get('isLogged');
        };

        $scope.loginAsGuest = function (data) {
          srvLogInOut.loginAsGuest();
        };

        $scope.logOff = function (data) {
          srvLogInOut.logOff();
        };

        $scope.loginWindow = function (data) {
          ngDialog.open({template: 'views/login_popup.html'});
        };

        $scope.login = function (data) {
          srvLogInOut.login(
            function (data) {
              if (data.status == 'error')
                alert($translate.instant('LOGIN_ERROR'));
            });
        };

        $scope.newUserWindow = function (data) {
          ngDialog.open({template: 'views/new_user_popup.html'});
        };

        $scope.userSettingsWindow = function (data) {
          ngDialog.open({template: 'views/user_settings_popup.html'});
        };
      }])
  .controller('usersController',
    ['$scope',
      '$translate',
      '$timeout',
      '$interval',
      '$cookieStore',
      'srvUsers',
      'ngDialog',
      function ($scope, $translate, $timeout, $interval, $cookieStore, srvUsers, ngDialog) {
        var init = function () {
          srvUsers.getUserMail(
            function (data) {
              $scope.newMailAddress = data;
            });
        };
        init();

        $scope.changeMailAddress = function () {
          var newMailAddress = document.getElementById('newMailAddress').value;
          srvUsers.setUserMail(newMailAddress, function (data) {
            if (data.status == 'success') {
              alert($translate.instant('EMAIL_CHANGED_SUCCESSFULLY'));
            }
          });
        };

        $scope.changePassword = function () {
          if (document.getElementById('newPassword').value == document.getElementById('newPasswordConfirmation').value) {
            var newPassword = document.getElementById('newPassword').value;
            srvUsers.setUserPassword(newPassword, function (data) {
              if (data.status == 'success') {
                alert($translate.instant('PASSWORD_CHANGED_SUCCESSFULLY'));
              }
            });
          }
          else {
            alert($translate.instant('CHANGE_PASSWORD_CONFIRMATION'));
          }
        };

        $scope.newUserWindow = function (data) {
          ngDialog.open({template: 'views/new_user_popup.html'});
        };

        $scope.addUser = function (data) {
          if (document.getElementById('addUserUsername').value == '') {
            ;
          }
          else if (document.getElementById('addUserPassword').value == document.getElementById('addUserPasswordConfirmation').value) {
            srvUsers.addUser(
              function (data) {
                if (data.status == 'error') {
                  alert($translate.instant('USER_EXIST'));
                }
                else {
                  ngDialog.close();
                  document.getElementById('addUserUsername').value = '';
                  document.getElementById('addUserPassword').value = '';
                  document.getElementById('addUserPasswordConfirmation').value = '';
                  document.getElementById('addUserMail').value = '';
                  alert($translate.instant('USER_ADDED_SUCCESSFULLY'));
                }
              });
          }
          else {
            alert($translate.instant('CHANGE_PASSWORD_CONFIRMATION'));
          }
        };

        $scope.deleteUser = function (username) {
          var password = '';
          if (document.getElementById('password') != null) {
            password = document.getElementById('password').value;
          }
          if (username == undefined) {
            username = $cookieStore.get('username');
          }
          srvUsers.deleteUser(username, password,
            function (data) {
              if (data.status == 'error') {
                alert($translate.instant('INVALID_PASSWORD_ERROR'));
              }
              else {
                if ($cookieStore.get('username') == username) {
                  $cookieStore.put('isLogged', false);
                  $cookieStore.put('username', '');
                  $cookieStore.put('isSuperuser', false);
                }
                ngDialog.close();
              }
            });
        }
        $scope.parseDate = function (id, lastLogin, joinedDate) {
          var lastLoginVar = '', joinedDateVar = '';
          if (lastLogin != '') {
            lastLoginVar = new Date(lastLogin).toString();
          }
          if (joinedDate != '') {
            joinedDateVar = new Date(joinedDate).toString();
          }
          document.getElementById('lastLogin_' + id).innerHTML = lastLoginVar.substring(0, lastLoginVar.indexOf("GMT"));
          document.getElementById('joinedDate_' + id).innerHTML = joinedDateVar.substring(0, joinedDateVar.indexOf("GMT"));
        };
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvUsers.getUsers(
            function (data) {
              $scope.users = data;
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }])
  .controller('settingsController', //settings
    ['$scope',
      'defaultValues',
      'srvLogs',
      function ($scope, defaultValues, srvLogs) {
        $scope.defaultK = defaultValues.getDefaultValues().k;
        $scope.defaultT = defaultValues.getDefaultValues().T;
        $scope.defaultInsertSizeMeanInward = defaultValues.getDefaultValues().insertSizeMeanInward;
        $scope.defaultInsertSizeStdDevInward = defaultValues.getDefaultValues().insertSizeStdDevInward;
        $scope.defaultInsertSizeMeanOutward = defaultValues.getDefaultValues().insertSizeMeanOutward;
        $scope.defaultInsertSizeStdDevOutward = defaultValues.getDefaultValues().insertSizeStdDevOutward;
        $scope.defaultGenomeLength = defaultValues.getDefaultValues().genomeLength;
        $scope.defaultBfcounterThreshold = defaultValues.getDefaultValues().bfcounterThreshold;
        $scope.defaultSingleEdgeCounterThreshold = defaultValues.getDefaultValues().singleEdgeCounterThreshold;
        $scope.defaultPairedReadsPetThresholdFrom = defaultValues.getDefaultValues().pairedReadsPetThresholdFrom;
        $scope.defaultPairedReadsPetThresholdTo = defaultValues.getDefaultValues().pairedReadsPetThresholdTo;
        $scope.defaultPairedReadsMpThresholdFrom = defaultValues.getDefaultValues().pairedReadsMpThresholdFrom;
        $scope.defaultPairedReadsMpThresholdTo = defaultValues.getDefaultValues().pairedReadsMpThresholdTo;
        document.getElementById('defaultAssemblyResultNotificationCheckbox').checked = defaultValues.getDefaultValues().assemblyResultNotification;
        document.getElementById('defaultAssemblyShowResultUrlCheckbox').checked = defaultValues.getDefaultValues().assemblyShowResultUrl;
        document.getElementById('defaultAlignAlgorithm').value = defaultValues.getDefaultValues().alignAlgorithm;
        document.getElementById('defaultIsCircular').checked = defaultValues.getDefaultValues().isCircular;
        document.getElementById('defaultAlignResultNotificationCheckbox').checked = defaultValues.getDefaultValues().alignResultNotification;
        document.getElementById('defaultAlignShowResultUrlCheckbox').checked = defaultValues.getDefaultValues().alignShowResultUrl;
        $scope.defaultGapPenalty = defaultValues.getDefaultValues().gapPenalty;
        $scope.defaultAA = defaultValues.getDefaultValues().AA;
        $scope.defaultAC = defaultValues.getDefaultValues().AC;
        $scope.defaultAG = defaultValues.getDefaultValues().AG;
        $scope.defaultAT = defaultValues.getDefaultValues().AT;
        $scope.defaultCA = defaultValues.getDefaultValues().CA;
        $scope.defaultCC = defaultValues.getDefaultValues().CC;
        $scope.defaultCG = defaultValues.getDefaultValues().CG;
        $scope.defaultCT = defaultValues.getDefaultValues().CT;
        $scope.defaultGA = defaultValues.getDefaultValues().GA;
        $scope.defaultGC = defaultValues.getDefaultValues().GC;
        $scope.defaultGG = defaultValues.getDefaultValues().GG;
        $scope.defaultGT = defaultValues.getDefaultValues().GT;
        $scope.defaultTA = defaultValues.getDefaultValues().TA;
        $scope.defaultTC = defaultValues.getDefaultValues().TC;
        $scope.defaultTG = defaultValues.getDefaultValues().TG;
        $scope.defaultTT = defaultValues.getDefaultValues().TT;
        $scope.defaultKmerSize = defaultValues.getDefaultValues().kmerSize;
        $scope.defaultDistance = defaultValues.getDefaultValues().distance;
        $scope.defaultStep = defaultValues.getDefaultValues().step;
        $scope.defaultMinLinks = defaultValues.getDefaultValues().minLinks;
        $scope.defaultMaxRatio = defaultValues.getDefaultValues().maxRatio;
        $scope.defaultMinContigLength = defaultValues.getDefaultValues().minContigLength;
        $scope.changeSettings = function (defaultK, defaultT, defaultInsertSizeMeanInward, defaultInsertSizeStdDevInward, defaultInsertSizeMeanOutward, defaultInsertSizeStdDevOutward, defaultGenomeLength, defaultBfcounterThreshold, defaultSimpleEdgeCounterThreshold, defaultPairedReadsPetThresholdFrom, defaultPairedReadsPetThresholdTo, defaultPairedReadsMpThresholdFrom, defaultPairedReadsMpThresholdTo) {
          var defaultAssemblyResultNotification = document.getElementById('defaultAssemblyResultNotificationCheckbox').checked;
          var defaultAssemblyShowResultUrl = document.getElementById('defaultAssemblyShowResultUrlCheckbox').checked;
          $scope.defaultK = defaultK;
          $scope.defaultT = defaultT;
          $scope.defaultInsertSizeMeanInward = defaultInsertSizeMeanInward;
          $scope.defaultInsertSizeStdDevInward = defaultInsertSizeStdDevInward;
          $scope.defaultInsertSizeMeanOutward = defaultInsertSizeMeanOutward;
          $scope.defaultInsertSizeStdDevOutward = defaultInsertSizeStdDevOutward;
          $scope.defaultGenomeLength = defaultGenomeLength;
          $scope.defaultSimpleEdgeCounterThreshold = defaultSimpleEdgeCounterThreshold;
          $scope.defaultPairedReadsPetThresholdFrom = defaultPairedReadsPetThresholdFrom;
          $scope.defaultPairedReadsPetThresholdTo = defaultPairedReadsPetThresholdTo;
          $scope.defaultPairedReadsMpThresholdFrom = defaultPairedReadsMpThresholdFrom;
          $scope.defaultPairedReadsMpThresholdTo = defaultPairedReadsMpThresholdTo;
          defaultValues.setDefaultValues(defaultK, defaultT, defaultInsertSizeMeanInward, defaultInsertSizeStdDevInward, defaultInsertSizeMeanOutward, defaultInsertSizeStdDevOutward, defaultGenomeLength, defaultBfcounterThreshold, defaultSimpleEdgeCounterThreshold, defaultPairedReadsPetThresholdFrom, defaultPairedReadsPetThresholdTo, defaultPairedReadsMpThresholdFrom, defaultPairedReadsMpThresholdTo, defaultAssemblyResultNotification, defaultAssemblyShowResultUrl);
        };
        $scope.changeAlignSettings = function (defaultGapPenalty, defaultAA, defaultAC, defaultAG, defaultAT, defaultCA, defaultCC, defaultCG, defaultCT, defaultGA, defaultGC, defaultGG, defaultGT, defaultTA, defaultTC, defaultTG, defaultTT) {
          var defaultAlignAlgorithm = document.getElementById('defaultAlignAlgorithm').value;
          var defaultIsCircular = document.getElementById('defaultIsCircular').checked;
          var defaultAlignResultNotification = document.getElementById('defaultAlignResultNotificationCheckbox').checked;
          var defaultAlignShowResultUrl = document.getElementById('defaultAlignShowResultUrlCheckbox').checked;
          $scope.defaultAlignAlgorithm = defaultAlignAlgorithm;
          $scope.defaultIsCircular = defaultIsCircular;
          $scope.defaultAlignResultNotification = defaultAlignResultNotification;
          $scope.defaultAlignShowResultUrl = defaultAlignShowResultUrl;
          $scope.defaultGapPenalty = defaultGapPenalty;
          $scope.defaultAA = defaultAA;
          $scope.defaultAC = defaultAC;
          $scope.defaultAG = defaultAG;
          $scope.defaultAT = defaultAT;
          $scope.defaultCA = defaultCA;
          $scope.defaultCC = defaultCC;
          $scope.defaultCG = defaultCG;
          $scope.defaultCT = defaultCT;
          $scope.defaultGA = defaultGA;
          $scope.defaultGC = defaultGC;
          $scope.defaultGG = defaultGG;
          $scope.defaultGT = defaultGT;
          $scope.defaultTA = defaultTA;
          $scope.defaultTC = defaultTC;
          $scope.defaultTG = defaultTG;
          $scope.defaultTT = defaultTT;
          defaultValues.setDefaultAlignValues(defaultAlignAlgorithm, defaultIsCircular, defaultAlignResultNotification, defaultAlignShowResultUrl, defaultGapPenalty, defaultAA, defaultAC, defaultAG, defaultAT, defaultCA, defaultCC, defaultCG, defaultCT, defaultGA, defaultGC, defaultGG, defaultGT, defaultTA, defaultTC, defaultTG, defaultTT);
        };
        $scope.changeScaffolderSettings = function (defaultKmerSize, defaultDistance, defaultStep, defaultMinLinks, defaultMaxRatio, defaultMinContigLength) {
          $scope.defaultKmerSize = defaultKmerSize;
          $scope.defaultDistance = defaultDistance;
          $scope.defaultStep = defaultStep;
          $scope.defaultMinLinks = defaultMinLinks;
          $scope.defaultMaxRatio = defaultMaxRatio;
          $scope.defaultMinContigLength = defaultMinContigLength;
          defaultValues.setDefaultScaffolderValues(defaultKmerSize, defaultDistance, defaultStep, defaultMinLinks, defaultMaxRatio, defaultMinContigLength);
        };
        $scope.showLogs = function () {
          var RE = /^[0-9]+$/;
          if (document.getElementById('logNumberLines').value.match(RE)) {
            srvLogs.getLogs(
              document.getElementById('logNumberLines').value, function (data) {
                document.getElementById('logs').value = data;
              });
          }
        };
      }])
  .controller('exitController',
    function ($scope, $window, $location, srvLogInOut) {
      $window.onbeforeunload = function (evt) {
        srvLogInOut.logOff();
        $location.path('/start_page');
      }
    })

  .controller('versionController', //versions of system modules
    ['$scope',
      'srvInfo',
      function ($scope, srvInfo) {
        srvInfo.getVersion(
          function (data) {
            $scope.server_ver = data;
          });
        $scope.client_ver = client_ver_major.toString() + '.' + client_ver_minor.toString() + '.' + client_ver_compilation.toString(); //from version.js file
      }])
  .controller('currentController', //current server params
    ['$scope',
      '$timeout',
      '$interval',
      'srvInfo',
      function ($scope, $timeout, $interval, srvInfo) {
        var REFRESH_INTERVAL = 1000; //ms
        var call = function () { //function called periodically
          srvInfo.getCurrent(
            function (data) {
              $scope.current = data;
            });
        };
        var timer = $timeout(call, 0);
        var intervaler = $interval(call, REFRESH_INTERVAL);
        $scope.$on("$destroy", function (event) {
          $timeout.cancel(timer);
          $interval.cancel(intervaler);
        });
      }]);
