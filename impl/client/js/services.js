/// @file services.js
/// @brief AngularJS services, AJAX communication with the server

angular.module('myAppServices', ['ngCookies', 'ngDialog'])
  .service('srvAssembling',
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getTaskResult = function (taskId, callback) {
        var data = 'id=' + taskId;
        return $http.get(this.baseURL + 'assembly/get_task_result?' + data).success(callback);
      };
      this.deleteTask = function (taskId) {
        var url = this.baseURL + 'assembly/delete/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.breakTask = function (taskId) {
        var url = this.baseURL + 'assembly/break_assembly_task/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.getCommands = function (callback) {
        return $http.get(this.baseURL + 'dnaasmpy/get_commands').success(callback);
      };
      this.getAssemblyTaskDocfile = function (taskId, callback) {
        var data = 'id=' + taskId;
        return $http.get(this.baseURL + 'assembly/get_assembly_task_docfile?' + data).success(callback);
      };
      this.addTask = function (callback) {
        var i1_1_file_name = document.getElementById('add_i1_1').value,
          i1_2_file_name = document.getElementById('add_i1_2').value,
          o1_1_file_name = document.getElementById('add_o1_1').value,
          o1_2_file_name = document.getElementById('add_o1_2').value,
          url = this.baseURL + 'assembly/insert/',
          addTaskName = document.getElementById('addTaskName').value,
          addK = document.getElementById('addK').value,
          addGenomeLength = document.getElementById('addGenomeLength').value,
          addInsertSizeMeanInward = 0.0,
          addInsertSizeStdDevInward = 0.0,
          addInsertSizeMeanOutward = 0.0,
          addInsertSizeStdDevOutward = 0.0,
          addPairedReadsAlgorithm = document.getElementById('addPairedReadsAlgorithm').value,
          addQualityThreshold = document.getElementById('addT').value,
          addBfcounterThreshold = document.getElementById('addBfcounterThreshold').value,
          addSingleEdgeCounterThreshold = document.getElementById('addSingleEdgeCounterThreshold').value,
          addPairedReadsPetThresholdFrom = 0,
          addPairedReadsPetThresholdTo = 0,
          addPairedReadsMpThresholdFrom = 0,
          addPairedReadsMpThresholdTo = 0,
          addCorrect = document.getElementById('addCorrect').checked,
          addResultNotification = document.getElementById('addTask_assemblyResultNotificationCheckbox').checked,
          addMailAddress = document.getElementById('addTask_assemblyMailAddress').value;

        if (addPairedReadsAlgorithm == '1') {
          addInsertSizeMeanInward = document.getElementById('addInsertSizeMeanInward').value;
          addInsertSizeStdDevInward = document.getElementById('addInsertSizeStdDevInward').value;
          addInsertSizeMeanOutward = document.getElementById('addInsertSizeMeanOutward').value;
          addInsertSizeStdDevOutward = document.getElementById('addInsertSizeStdDevOutward').value;
          addPairedReadsPetThresholdFrom = document.getElementById('addPairedReadsPetThresholdFrom').value;
          addPairedReadsPetThresholdTo = document.getElementById('addPairedReadsPetThresholdTo').value;
          addPairedReadsMpThresholdFrom = document.getElementById('addPairedReadsMpThresholdFrom').value;
          addPairedReadsMpThresholdTo = document.getElementById('addPairedReadsMpThresholdTo').value;
        }

        var data = 'name=' + addTaskName
          + '&i1_1_file_name=' + i1_1_file_name
          + '&i1_2_file_name=' + i1_2_file_name
          + '&o1_1_file_name=' + o1_1_file_name
          + '&o1_2_file_name=' + o1_2_file_name
          + '&k=' + addK
          + '&genome_length=' + addGenomeLength
          + '&insert_size_mean_inward=' + addInsertSizeMeanInward
          + '&insert_size_std_dev_inward=' + addInsertSizeStdDevInward
          + '&insert_size_mean_outward=' + addInsertSizeMeanOutward
          + '&insert_size_std_dev_outward=' + addInsertSizeStdDevOutward
          + '&paired_reads_algorithm=' + addPairedReadsAlgorithm
          + '&quality_threshold=' + addQualityThreshold
          + '&bfcounter_threshold=' + addBfcounterThreshold
          + '&single_edge_counter_threshold=' + addSingleEdgeCounterThreshold
          + '&paired_reads_pet_threshold_from=' + addPairedReadsPetThresholdFrom
          + '&paired_reads_pet_threshold_to=' + addPairedReadsPetThresholdTo
          + '&paired_reads_mp_threshold_from=' + addPairedReadsMpThresholdFrom
          + '&paired_reads_mp_threshold_to=' + addPairedReadsMpThresholdTo
          + '&correct=' + addCorrect
          + '&result_notification=' + addResultNotification
          + '&mail_address=' + addMailAddress;

        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.updateTask = function (taskId, callback) {
        var i1_1_file_name = document.getElementById('update_i1_1').value,
          i1_2_file_name = document.getElementById('update_i1_2').value,
          o1_1_file_name = document.getElementById('update_o1_1').value,
          o1_2_file_name = document.getElementById('update_o1_2').value,
          url = this.baseURL + 'assembly/update/',
          //updateTaskName = document.getElementById('updateTaskName').value,
          updateK = document.getElementById('updateK').value,
          updateGenomeLength = document.getElementById('updateGenomeLength').value,
          updateInsertSizeMeanInward = document.getElementById('updateInsertSizeMeanInward').value,
          updateInsertSizeStdDevInward = document.getElementById('updateInsertSizeStdDevInward').value,
          updateInsertSizeMeanOutward = document.getElementById('updateInsertSizeMeanOutward').value,
          updateInsertSizeStdDevOutward = document.getElementById('updateInsertSizeStdDevOutward').value,
          updateT = document.getElementById('updateT').value,
          updateBfcounterThreshold = document.getElementById('updateBfcounterThreshold').value,
          updateSingleEdgeCounterThreshold = document.getElementById('updateSingleEdgeCounterThreshold').value,
          updatePairedReadsPetThresholdFrom = document.getElementById('updatePairedReadsPetThresholdFrom').value,
          updatePairedReadsPetThresholdTo = document.getElementById('updatePairedReadsPetThresholdTo').value,
          updatePairedReadsMpThresholdFrom = document.getElementById('updatePairedReadsMpThresholdFrom').value,
          updatePairedReadsMpThresholdTo = document.getElementById('updatePairedReadsMpThresholdTo').value,
          updatePairedReadsAlgorithm = document.getElementById('updatePairedReadsAlgorithm').value,
          updateCorrect = document.getElementById('updateCorrect').checked,
          updateResultNotification = document.getElementById('updateTask_assemblyResultNotificationCheckbox').checked,
          updateMailAddress = document.getElementById('updateTask_assemblyMailAddress').value,

          updateGenerateScaffold = document.getElementById('updateTask_generateScaffoldCheckbox').checked,
          updateKmerSize = document.getElementById('updateKmerSize').value,
          updateDistance = document.getElementById('updateDistance').value,
          updateStep = document.getElementById('updateStep').value,
          updateMinLinks = document.getElementById('updateMinLinks').value,
          updateMaxRatio = document.getElementById('updateMaxRatio').value,
          updateMinContigLength = document.getElementById('updateMinContigLength').value;
        var data = 'id=' + taskId
          + '&i1_1_file_name=' + i1_1_file_name
          + '&i1_2_file_name=' + i1_2_file_name
          + '&o1_1_file_name=' + o1_1_file_name
          + '&o1_2_file_name=' + o1_2_file_name
          + '&k=' + updateK
          + '&genome_length=' + updateGenomeLength
          + '&insert_size_mean_inward=' + updateInsertSizeMeanInward
          + '&insert_size_std_dev_inward=' + updateInsertSizeStdDevInward
          + '&insert_size_mean_outward=' + updateInsertSizeMeanOutward
          + '&insert_size_std_dev_outward=' + updateInsertSizeStdDevOutward
          + '&quality_threshold=' + updateT
          + '&bfcounter_threshold=' + updateBfcounterThreshold
          + '&single_edge_counter_threshold=' + updateSingleEdgeCounterThreshold
          + '&paired_reads_pet_threshold_from=' + updatePairedReadsPetThresholdFrom
          + '&paired_reads_pet_threshold_to=' + updatePairedReadsPetThresholdTo
          + '&paired_reads_mp_threshold_from=' + updatePairedReadsMpThresholdFrom
          + '&paired_reads_mp_threshold_to=' + updatePairedReadsMpThresholdTo
          + '&paired_reads_algorithm=' + updatePairedReadsAlgorithm
          + '&correct=' + updateCorrect
          + '&result_notification=' + updateResultNotification
          + '&mail_address=' + updateMailAddress
          + '&generate_scaffold=' + updateGenerateScaffold
          + '&kmer_size=' + updateKmerSize
          + '&distance=' + updateDistance
          + '&step=' + updateStep
          + '&min_links=' + updateMinLinks
          + '&max_ratio=' + updateMaxRatio
          + '&min_contig_length=' + updateMinContigLength;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
    })
  .service('srvAllAssembling',
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getAllAssemblyTasks = function (callback) {
        return $http.get(this.baseURL + 'assembly/get_all_assembly_tasks').success(callback);
      };
    })
  .service('srvUserAssembling',
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getUserAssemblyTasks = function (callback) {
        return $http.get(this.baseURL + 'assembly/get_user_assembly_tasks').success(callback);
      };
    })
  .service('srvAlignment', //alignment page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.alignSequence = function (callback) {
        var url = this.baseURL + 'align/insert/',
          name = document.getElementById('newAlignTaskName').value,
          seqFileName = document.getElementById('sequenceFile').value,
          refFileName = document.getElementById('referenceFile').value,
          align_algorithm = document.getElementById('alignAlgorithmSelect').value,
          circular = document.getElementById('circularCheckbox').checked,
          d = document.getElementById('gapPenalty').value,
          AA = document.getElementById('AA').value,
          AC = document.getElementById('AC').value,
          AG = document.getElementById('AG').value,
          AT = document.getElementById('AT').value,
          CA = document.getElementById('CA').value,
          CC = document.getElementById('CC').value,
          CG = document.getElementById('CG').value,
          CT = document.getElementById('CT').value,
          GA = document.getElementById('GA').value,
          GC = document.getElementById('GC').value,
          GG = document.getElementById('GG').value,
          GT = document.getElementById('GT').value,
          TA = document.getElementById('TA').value,
          TC = document.getElementById('TC').value,
          TG = document.getElementById('TG').value,
          TT = document.getElementById('TT').value,
          resultNotification = document.getElementById('alignResultNotificationCheckbox').checked,
          mailAddress = document.getElementById('alignMailAddress').value,
          data = 'name=' + name + '&seq_file_name=' + seqFileName + '&ref_file_name=' + refFileName + '&align_algorithm=' + align_algorithm + '&circular=' + circular + '&gap_penalty=' + d + '&AA=' + AA + '&AC=' + AC + '&AG=' + AG + '&AT=' + AT + '&CA=' + CA + '&CC=' + CC + '&CG=' + CG + '&CT=' + CT + '&GA=' + GA + '&GC=' + GC + '&GG=' + GG + '&GT=' + GT + '&TA=' + TA + '&TC=' + TC + '&TG=' + TG + '&TT=' + TT + '&result_notification=' + resultNotification + '&mail_address=' + mailAddress;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.deleteAlignTask = function (taskId) {
        var url = this.baseURL + 'align/delete/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.breakAlignTask = function (taskId) {
        var url = this.baseURL + 'align/break_align_task/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.getAlignTaskDocfile = function (taskId, callback) {
        var data = 'id=' + taskId;
        return $http.get(this.baseURL + 'align/get_align_task_docfile?' + data).success(callback);
      };
    })
  .service('srvAllAlignment', //all alignment task page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getAllAlignTasks = function (callback) {
        return $http.get(this.baseURL + 'align/get_all_align_tasks').success(callback);
      };
    })
  .service('srvUserAlignment', //user alignment task page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getUserAlignTasks = function (callback) {
        return $http.get(this.baseURL + 'align/get_user_align_tasks').success(callback);
      };
    })
  .service('srvScaffolding', //scaffolding page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.addScaffoldTask = function (callback) {
        var url = this.baseURL + 'scaffold/insert/',
          name = document.getElementById('newScaffoldTaskName').value,
          assemblyTask = '',
          contigsFileName = document.getElementById('contigsFile').value,
          longReadsFileName = document.getElementById('longReadsFile').value,
          kmerSize = document.getElementById('kmerSize').value,
          distance = document.getElementById('distance').value,
          step = document.getElementById('step').value,
          minLinks = document.getElementById('minLinks').value,
          maxRatio = document.getElementById('maxRatio').value,
          minContigLength = document.getElementById('minContigLength').value,

          data = 'name=' + name
            + '&assembly_task=' + assemblyTask
            + '&contigs_file_name=' + contigsFileName
            + '&long_reads_file_name=' + longReadsFileName
            + '&kmer_size=' + kmerSize
            + '&distance=' + distance
            + '&step=' + step
            + '&min_links=' + minLinks
            + '&max_ratio=' + maxRatio
            + '&min_contig_length=' + minContigLength;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.addDelayedScaffoldTask = function (taskName, assemblyTaskName, callback) {
        var url = this.baseURL + 'scaffold/insert/',
          contigsFileName = '',
          longReadsFileName = document.getElementById('add_long_reads').value,
          kmerSize = document.getElementById('addKmerSize').value,
          distance = document.getElementById('addDistance').value,
          step = document.getElementById('addStep').value,
          minLinks = document.getElementById('addMinLinks').value,
          maxRatio = document.getElementById('addMaxRatio').value,
          minContigLength = document.getElementById('addMinContigLength').value,

          data = 'name=' + taskName
            + '&assembly_task=' + assemblyTaskName
            + '&contigs_file_name=' + contigsFileName
            + '&long_reads_file_name=' + longReadsFileName
            + '&kmer_size=' + kmerSize
            + '&distance=' + distance
            + '&step=' + step
            + '&min_links=' + minLinks
            + '&max_ratio=' + maxRatio
            + '&min_contig_length=' + minContigLength;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.deleteScaffoldTask = function (taskId) {
        var url = this.baseURL + 'scaffold/delete/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.breakScaffoldTask = function (taskId) {
        var url = this.baseURL + 'scaffold/break_scaffold_task/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.getScaffoldTaskDocfile = function (taskId, callback) {
        var data = 'id=' + taskId;
        return $http.get(this.baseURL + 'scaffold/get_scaffold_task_docfile?' + data).success(callback);
      };
    })
  .service('srvAllScaffolding', //all scaffolding task page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getAllScaffoldTasks = function (callback) {
        return $http.get(this.baseURL + 'scaffold/get_all_scaffold_tasks').success(callback);
      };
    })
  .service('srvUserScaffolding', //user scaffolding task page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getUserScaffoldTasks = function (callback) {
        return $http.get(this.baseURL + 'scaffold/get_user_scaffold_tasks').success(callback);
      };
    })
  .service('srvOLC',
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.addTask = function (params, callback) {
         const data = 'name=' + params.newOLCTaskName
            + '&assembly_task=' + params.assemblyTask
            + '&long_reads_file_name=' + params.longReadsFile
            + '&kmer_length=' + params.kmerLength
            + '&sketch_num=' + params.sketchNum
            + '&min_jaccard_sim=' + params.minJaccardSim
            + '&match_score=' + params.matchScore
            + '&mismatch_score=' + params.mismatchScore
            + '&gap_penalty=' + params.gapPenalty
            + '&min_edge=' + params.minEdge
            + '&min_contig_length=' + params.minContigLength
            + '&path_width=' + params.pathWidth;
         console.log(params.longReadsFileName);

        return $http({
          method: 'POST',
          url: this.baseURL + 'olc/insert',
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };

      this.deleteOLCTask = function (taskId) {
        var url = this.baseURL + 'olc/delete/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.breakOLCTask = function (taskId) {
        var url = this.baseURL + 'olc/break_olc_task/',
          data = 'id=' + taskId;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.getOLCTaskDocfile = function (taskId, callback) {
        var data = 'id=' + taskId;
        return $http.get(this.baseURL + 'olc/get_olc_task_docfile?' + data).success(callback);
      };
    })
  .service('srvAllOLC', //all olc task page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getAllOLCTasks = function (callback) {
        return $http.get(this.baseURL + 'olc/get_all_scaffold_tasks').success(callback);
      };
    })
  .service('srvUserOLC', //user olc task page
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getUserOLCTasks = function (callback) {
        return $http.get(this.baseURL + 'olc/get_user_olc_tasks').success(callback);
      };
    })
  .service('srvBstAssembling',
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js

      this.getAssemblyTaskDocfile = function (taskId, callback) {
        var data = 'id=' + taskId;
        return $http.get(this.baseURL + 'bst/get_assembly_task_docfile?' + data).then(
          function (response) {
            callback(response.data)
          }
        );
      };

      this.addTask = function (params, callback) {
        var data = 'task_name=' + params.taskName
          + '&input_file=' + params.inputFile
          + '&word_length=' + params.wordLength
          + '&min_word_count=' + params.minWordCount
          + '&max_word_count=' + params.maxWordCount
          + '&min_association=' + params.minAssociation
          + '&path_width=' + params.pathWidth

        return $http({
          method: 'POST',
          url: this.baseURL + 'bst/insert/',
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        }).then(
          function (response) {
            callback(response.data)
          });
      };
    })
  .service('srvFiles',
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getUserFiles = function (callback) {
        return $http.get(this.baseURL + 'file/get_user_files').success(callback);
      };
      this.getAllFiles = function (callback) {
        return $http.get(this.baseURL + 'file/get_all_files').success(callback);
      };
      this.uploadExampleFiles = function () {
        var url = this.baseURL + 'file/upload_example_files/',
          data = '';
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        });
      };
      this.getFileContents = function (docfile, callback) {
        var data = 'docfile=' + docfile;
        return $http.get(this.baseURL + 'file/get_file_contents?' + data)
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.deleteFile = function (docfile, callback) {
        var url = this.baseURL + 'file/delete_file/',
          data = 'docfile=' + docfile;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.downloadFile = function (docfile, fileName) {
        var url = this.baseURL + 'file/download_file/',
          data = 'docfile=' + docfile;

        function updateProgress(oEvent) {
          if (oEvent.lengthComputable) {
            var percentComplete = oEvent.loaded / oEvent.total;
            console.log('Downloading ' + docfile + ' from a server - ' + (percentComplete * 100).toFixed(2) + '%');
            if (document.getElementById('downloadProgress_' + docfile) != null) {
              document.getElementById('downloadProgress_' + docfile).innerHTML = (percentComplete * 100).toFixed(2) + '%';
            }
          } else {
            alert("Unable to compute progress information since the total size is unknown");
          }
        }

        function transferComplete(evt) {
          //save file
          var a = window.document.createElement('a');
          a.href = window.URL.createObjectURL(
            new Blob([xhttp.responseText], {type: 'application/octet-stream'})
          );
          a.download = fileName;
          document.body.appendChild(a);
          a.click();
          document.body.removeChild(a);
          if (document.getElementById('downloadProgress_' + docfile) != null) {
            document.getElementById('downloadProgress_' + docfile).innerHTML = '';
          }
        }

        function transferFailed(evt) {
          alert("An error occurred while transferring the file.");
          if (document.getElementById('downloadProgress_' + docfile) != null) {
            document.getElementById('downloadProgress_' + docfile).innerHTML = '';
          }
        }

        var xhttp = new XMLHttpRequest();
        xhttp.addEventListener("progress", updateProgress, false);
        xhttp.addEventListener("load", transferComplete, false);
        xhttp.addEventListener("error", transferFailed, false);
        xhttp.open("POST", url, true);
        xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
        xhttp.send(data);
      };
      this.uploadFile = function (file) {
        // progress on transfers for client - server (for uploading files only)
        function updateProgress(oEvent) {
          if (oEvent.lengthComputable) {
            var percentComplete = oEvent.loaded / oEvent.total;
            console.log('Sending ' + file.name + ' to a server - ' + (percentComplete * 100).toFixed(2) + '%');
            if (document.getElementById("uploadProgress") != null) {
              document.getElementById('uploadProgress').innerHTML = (percentComplete * 100).toFixed(2) + '%';
              document.getElementById('uploadFileName').innerHTML = file.name;
            }
          } else {
            alert("Unable to compute progress information since the total size is unknown");
          }
          if (document.getElementById('uploadFile') != undefined) {
            document.getElementById('uploadFile').disabled = true;
            document.getElementById('chooseUploadFile').disabled = true;
          }
        }

        function transferComplete(evt) {
          if (document.getElementById("uploadProgress") != null) {
            document.getElementById('uploadProgress').innerHTML = '';
            document.getElementById('uploadFileName').innerHTML = '';
          }
          if (document.getElementById('uploadFile') != undefined) {
            document.getElementById('uploadFile').disabled = false;
            document.getElementById('chooseUploadFile').disabled = false;
          }
        }

        function transferFailed(evt) {
          alert("An error occurred while transferring the file.");
          if (document.getElementById("uploadProgress") != null) {
            document.getElementById('uploadProgress').innerHTML = '';
            document.getElementById('uploadFileName').innerHTML = '';
          }
          if (document.getElementById('uploadFile') != undefined) {
            document.getElementById('uploadFile').disabled = false;
            document.getElementById('chooseUploadFile').disabled = false;
          }
        }

        var xhttp = new XMLHttpRequest();
        xhttp.upload.onprogress = updateProgress;
        xhttp.addEventListener("load", transferComplete, false);
        xhttp.addEventListener("error", transferFailed, false);

        var uploadUrl = this.baseURL + 'file/upload_file/';
        var fd = new FormData();
        fd.append('file', file);
        xhttp.open("POST", uploadUrl, true);
        xhttp.send(fd);
      };
    })
  .service('srvSplitFiles',
    function ($http) {
      this.splitFiles = function (files, callback) {
        if (files == undefined) {
          return;
        }
        files_fasta = [];
        files_fastq = [];
        files_vcf = [];
        files_unknown = [];
        var numOfFiles = Object.keys(files).length;
        for (i = 0; i < numOfFiles; i++) {
          switch (files[i].file_format) {
            case 'FA':
              files_fasta.push(files[i]);
              break;
            case 'FQ':
              files_fastq.push(files[i]);
              break;
            case 'VCF':
              files_vcf.push(files[i]);
              break;
            default:
              files_unknown.push(files[i]);
          }
        }
        callback({
          "files_fasta": files_fasta,
          "files_fastq": files_fastq,
          "files_vcf": files_vcf,
          "files_unknown": files_unknown
        });
      };
    })
  .service('srvLogInOut',
    function ($http, $cookieStore, ngDialog) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.login = function (callback) {
        var url = this.baseURL + 'user/login_user/',
          username = document.getElementById('username').value,
          password = document.getElementById('password').value,
          data = 'username=' + username + '&password=' + password;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            if (data.status == 'error') {
              callback(data);
            }
            else {
              $cookieStore.put('isLogged', true);
              $cookieStore.put('username', username);
              $cookieStore.put('isSuperuser', data.isSuperuser);
              ngDialog.close();
            }
          });
      };
      this.logOff = function (callback) {
        var url = this.baseURL + 'user/logout_user/',
          data = '';
        $cookieStore.put('isLogged', false);
        $cookieStore.put('username', '');
        $cookieStore.put('isSuperuser', false);
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .success(function (data) {
          });
      };
      this.loginAsGuest = function (callback) {
        var url = this.baseURL + 'user/add_and_login_guest_user/',
          data = '';
        $cookieStore.put('isLogged', false);
        $cookieStore.put('username', '');
        $cookieStore.put('isSuperuser', false);
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            if (data.status == 'error') {
              callback(data);
            }
            else {
              $cookieStore.put('isLogged', true);
              $cookieStore.put('username', data.username);
              $cookieStore.put('isSuperuser', false);
            }
          });
      };

    })
  .service('srvUsers',
    function ($http, $cookieStore, ngDialog) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix is defined in version.js
      this.getUsers = function (callback) {
        return $http.get(this.baseURL + 'user/get_users').success(callback);
      };
      this.getUserMail = function (callback) {
        return $http.get(this.baseURL + 'user/get_user_mail').success(callback);
      };
      this.setUserPassword = function (newPassword, callback) {
        var url = this.baseURL + 'user/set_user_password/',
          data = 'new_password=' + newPassword;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.setUserMail = function (newMail, callback) {
        var url = this.baseURL + 'user/set_user_mail/',
          data = 'new_mail=' + newMail;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.deleteUser = function (username, password, callback) {
        var url = this.baseURL + 'user/delete_user/',
          data = 'username=' + username + '&password=' + password;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
      this.addUser = function (callback) {
        var url = this.baseURL + 'user/add_user/',
          username = document.getElementById('addUserUsername').value,
          password = document.getElementById('addUserPassword').value,
          mail = document.getElementById('addUserMail').value,
          data = 'username=' + username + '&password=' + password + '&mail=' + mail;
        return $http({
          method: 'POST',
          url: url,
          data: data,
          headers: {'Content-Type': 'application/x-www-form-urlencoded'}
        })
          .error(function (data) {
            console.log(data);
            callback(data);
          })
          .success(function (data) {
            console.log(data);
            callback(data);
          });
      };
    })
  .service('defaultValues',
    function () {
      var defaultValues = {
        k: '55',
        T: '10',
        insertSizeMeanInward: '200.0',
        insertSizeStdDevInward: '20.0',
        insertSizeMeanOutward: '2000.0',
        insertSizeStdDevOutward: '200.0',
        genomeLength: '4000000',
        bfcounterThreshold: '0',
        singleEdgeCounterThreshold: '5',
        pairedReadsPetThresholdFrom: '2',
        pairedReadsPetThresholdTo: '4',
        pairedReadsMpThresholdFrom: '2',
        pairedReadsMpThresholdTo: '4',
        assemblyResultNotification: false,
        assemblyShowResultUrl: false,
        gapPenalty: '-1',
        AA: '1',
        AC: '-1',
        AG: '-1',
        AT: '-1',
        CA: '-1',
        CC: '1',
        CG: '-1',
        CT: '-1',
        GA: '-1',
        GC: '-1',
        GG: '1',
        GT: '-1',
        TA: '-1',
        TC: '-1',
        TG: '-1',
        TT: '1',
        alignAlgorithm: 'hirschberg',
        isCircular: false,
        alignResultNotification: false,
        alignShowResultUrl: false,
        kmerSize: '15',
        distance: '4000',
        step: '2',
        minLinks: '5',
        maxRatio: '0.3',
        minContigLength: '500',
        kmerLength: '11',
        sketchNum: '256',
        minJaccardSim: '0.5',
        matchScore: '1',
        mismatchScore: '-1',
        gapPenalty: '-1',
        minEdge: '1000',
        minContigLength: '10000',
        pathWidth: '1'
      };
      return {
        setDefaultValues: function (defaultK, defaultT, defaultInsertSizeMeanInward, defaultInsertSizeStdDevInward, defaultInsertSizeMeanOutward, defaultInsertSizeStdDevOutward, defaultGenomeLength, defaultBfcounterThreshold, defaultSingleEdgeCounterThreshold, defaultPairedReadsPetThresholdFrom, defaultPairedReadsPetThresholdTo, defaultPairedReadsMpThresholdFrom, defaultPairedReadsMpThresholdTo, defaultAssemblyResultNotification, defaultAssemblyShowResultUrl) {
          defaultValues.k = defaultK;
          defaultValues.T = defaultT;
          defaultValues.insertSizeMeanInward = defaultInsertSizeMeanInward;
          defaultValues.insertSizeStdDevInward = defaultInsertSizeStdDevInward;
          defaultValues.insertSizeMeanOutward = defaultInsertSizeMeanOutward;
          defaultValues.insertSizeStdDevOutward = defaultInsertSizeStdDevOutward;
          defaultValues.genomeLength = defaultGenomeLength;
          defaultValues.bfcounterThreshold = defaultBfcounterThreshold;
          defaultValues.singleEdgeCounterThreshold = defaultSingleEdgeCounterThreshold;
          defaultValues.pairedReadsPetThresholdFrom = defaultPairedReadsPetThresholdFrom;
          defaultValues.pairedReadsPetThresholdTo = defaultPairedReadsPetThresholdTo;
          defaultValues.pairedReadsMpThresholdFrom = defaultPairedReadsMpThresholdFrom;
          defaultValues.pairedReadsMpThresholdTo = defaultPairedReadsMpThresholdTo;
          defaultValues.assemblyResultNotification = defaultAssemblyResultNotification;
          defaultValues.assemblyShowResultUrl = defaultAssemblyShowResultUrl;
        },
        setDefaultAlignValues: function (defaultAlignAlgorithm, defaultIsCircular, defaultAlignResultNotification, defaultAlignShowResultUrl, defaultGapPenalty, defaultAA, defaultAC, defaultAG, defaultAT, defaultCA, defaultCC, defaultCG, defaultCT, defaultGA, defaultGC, defaultGG, defaultGT, defaultTA, defaultTC, defaultTG, defaultTT) {
          defaultValues.alignAlgorithm = defaultAlignAlgorithm;
          defaultValues.isCircular = defaultIsCircular;
          defaultValues.alignResultNotification = defaultAlignResultNotification;
          defaultValues.alignShowResultUrl = defaultAlignShowResultUrl;
          defaultValues.gapPenalty = defaultGapPenalty;
          defaultValues.AA = defaultAA;
          defaultValues.AC = defaultAC;
          defaultValues.AG = defaultAG;
          defaultValues.AT = defaultAT;
          defaultValues.CA = defaultCA;
          defaultValues.CC = defaultCC;
          defaultValues.CG = defaultCG;
          defaultValues.CT = defaultCT;
          defaultValues.GA = defaultGA;
          defaultValues.GC = defaultGC;
          defaultValues.GG = defaultGG;
          defaultValues.GT = defaultGT;
          defaultValues.TA = defaultTA;
          defaultValues.TC = defaultTC;
          defaultValues.TG = defaultTG;
          defaultValues.TT = defaultTT;
        },
        setDefaultScaffolderValues: function (defaultKmerSize, defaultDistance, defaultStep, defaultMinLinks, defaultMaxRatio, defaultMinContigLength) {
          defaultValues.kmerSize = defaultKmerSize;
          defaultValues.distance = defaultDistance;
          defaultValues.step = defaultStep;
          defaultValues.minLinks = defaultMinLinks;
          defaultValues.maxRatio = defaultMaxRatio;
          defaultValues.minContigLength = defaultMinContigLength;
        },
        getDefaultValues: function () {
          return defaultValues;
        }
      }
    })
  .service('srvLogs', //server logs
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix defined in version.js
      this.getLogs = function (numberOfLines, callback) {
        var data = 'number_of_lines=' + numberOfLines;
        return $http.get(this.baseURL + 'logs/get_logs?' + data).success(callback);
      };
    })
  .service('srvInfo', //current information from server
    function ($http) {
      this.baseURL = client_server_prefix + '/ajax/'; //the prefix defined in version.js
      this.getVersion = function (callback) {
        return $http.get(this.baseURL + 'version/get').success(callback);
      };
      this.getCurrent = function (callback) {
        return $http.get(this.baseURL + 'current/get').success(callback);
      };
    });
